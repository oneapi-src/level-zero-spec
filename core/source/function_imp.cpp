#define FUNCTION_INTERNAL
#include "function_imp.h"
#undef FUNCTION_INTERNAL

#define MODULE_INTERNAL
#include "module_imp.h"
#undef MODULE_INTERNAL

#include "device.h"
#include "graphics_allocation.h"
#include "memory_manager.h"
#include "mocs_mapper.h"
#include "module.h"
#include "image.h"
#include "printf_handler.h"

#include "runtime/context/context.h"
#include "runtime/helpers/basic_math.h"
#include "runtime/helpers/per_thread_data.h"
#include "runtime/helpers/string.h"
#include "runtime/kernel/kernel.h"
#include "runtime/mem_obj/buffer.h"
#include "runtime/program/kernel_arg_info.h"
#include "runtime/program/program.h"

#include <cassert>
#include <memory>

namespace NEO_temporary {
struct LightweightOclKernel : public NEO::Kernel {
    LightweightOclKernel(NEO::Program *program, const NEO::KernelInfo &kernelInfo)
        : Kernel(program, kernelInfo, program->getDevice(0), false) {
    }

    using Kernel::kernelArgHandlers;
    using Kernel::kernelArguments;
    using Kernel::kernelSvmGfxAllocations;

    using Kernel::localBindingTableOffset;
    using Kernel::numberOfBindingTableStates;
    using Kernel::pSshLocal;
    using Kernel::sshLocalSize;

    using Kernel::crossThreadData;
    using Kernel::crossThreadDataSize;

    using Kernel::privateSurface;
    using Kernel::privateSurfaceSize;

    using Kernel::auxTranslationRequired;
    using Kernel::patchedArgumentsNum;
    using Kernel::startOffset;
    using Kernel::usingImagesOnly;
    using Kernel::usingSharedObjArgs;

    using Kernel::kernelInfo;
};
} // namespace NEO_temporary

namespace NEO {
namespace Math {
using namespace ::Math; // just to emphasize the origin (wich originally is not encapsulated in OCLRT)
}
using KernelArgInfo = ::KernelArgInfo;
} // namespace NEO

namespace L0 {

struct FunctionImp::OCLInternal { // cloned from NEO::Kernel - keeping types/names the same for simplicity
    std::vector<NEO::Kernel::SimpleKernelArgInfo> kernelArguments;
    std::vector<FunctionImp::FunctionArgHandler> kernelArgHandlers;
    std::vector<NEO::GraphicsAllocation *> kernelSvmGfxAllocations;

    void storeKernelArg(uint32_t argIndex, NEO::Kernel::kernelArgType argType, void *argObject,
                        const void *argValue, size_t argSize,
                        NEO::GraphicsAllocation *argSvmAlloc = nullptr, cl_mem_flags argSvmFlags = 0) {
        kernelArguments[argIndex].type = argType;
        kernelArguments[argIndex].object = argObject;
        kernelArguments[argIndex].value = argValue;
        kernelArguments[argIndex].size = argSize;
        kernelArguments[argIndex].pSvmAlloc = argSvmAlloc;
        kernelArguments[argIndex].svmFlags = argSvmFlags;
    }

    size_t numberOfBindingTableStates = 0;
    size_t localBindingTableOffset = 0;
    std::unique_ptr<char[]> pSshLocal = nullptr;
    uint32_t sshLocalSize = 0;

    bool usingSharedObjArgs = false;
    bool usingImagesOnly = false;
    bool auxTranslationRequired = false;
    uint32_t patchedArgumentsNum = 0;
    uint32_t startOffset = 0;
};

FunctionImp::FunctionImp(Module *module) : module(module), oclInternals(new OCLInternal) {}

FunctionImp::~FunctionImp() {
    if (perThreadDataForWholeThreadGroup) {
        alignedFree(perThreadDataForWholeThreadGroup);
    }
    if (kernelRT) {
        kernelRT->release();
    }
    if (printfBuffer) {
        module->getDevice()->getMemoryManager()->freeMemory(printfBuffer);
    }
    privateMemAllocation.deleteOwned();
    delete oclInternals;
    delete kernelArgBindingTableIndex;
}

xe_result_t FunctionImp::setArgumentValue(uint32_t argIndex,
                                          size_t argSize,
                                          const void *pArgValue) {
    assert(argIndex < oclInternals->kernelArgHandlers.size());
    (this->*oclInternals->kernelArgHandlers[argIndex])(argIndex, argSize, pArgValue);
    return XE_RESULT_SUCCESS;
}

void FunctionImp::setGroupCount(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    uint32_t groupSizeX;
    uint32_t groupSizeY;
    uint32_t groupSizeZ;
    getGroupSize(groupSizeX, groupSizeY, groupSizeZ);

    patchCrossThreadData(getKernelInfo()->workloadInfo.globalWorkSizeOffsets[0], groupCountX * groupSizeX);
    patchCrossThreadData(getKernelInfo()->workloadInfo.globalWorkSizeOffsets[1], groupCountY * groupSizeY);
    patchCrossThreadData(getKernelInfo()->workloadInfo.globalWorkSizeOffsets[2], groupCountZ * groupSizeZ);

    patchCrossThreadData(getKernelInfo()->workloadInfo.numWorkGroupsOffset[0], groupCountX);
    patchCrossThreadData(getKernelInfo()->workloadInfo.numWorkGroupsOffset[1], groupCountY);
    patchCrossThreadData(getKernelInfo()->workloadInfo.numWorkGroupsOffset[2], groupCountZ);
}

xe_result_t FunctionImp::setGroupSize(uint32_t groupSizeX,
                                      uint32_t groupSizeY,
                                      uint32_t groupSizeZ) {
    if ((0 == groupSizeX) || (0 == groupSizeY) || (0 == groupSizeZ)) {
        return XE_RESULT_ERROR_INVALID_PARAMETER; // needs clarification in the spec
    }

    auto numChannels = NEO::PerThreadDataHelper::getNumLocalIdChannels(*getKernelInfo()->patchInfo.threadPayload);
    Vec3<size_t> groupSize{groupSizeX, groupSizeY, groupSizeZ};
    auto itemsInGroup = NEO::Math::computeTotalElementsCount(groupSize);
    uint32_t perThreadDataSizeForWholeThreadGroupNeeded = static_cast<uint32_t>(NEO::PerThreadDataHelper::getPerThreadDataSizeTotal(getKernelInfo()->getMaxSimdSize(),
                                                                                                                                    numChannels, itemsInGroup));
    if (perThreadDataSizeForWholeThreadGroupNeeded > perThreadDataSizeForWholeThreadGroupAllocated) {
        alignedFree(perThreadDataForWholeThreadGroup);
        perThreadDataForWholeThreadGroup = alignedMalloc(perThreadDataSizeForWholeThreadGroupNeeded, 32); // alignment for vector instructions
        perThreadDataSizeForWholeThreadGroupAllocated = perThreadDataSizeForWholeThreadGroupNeeded;
    }
    perThreadDataSizeForWholeThreadGroup = perThreadDataSizeForWholeThreadGroupNeeded;

    if (numChannels > 0) {
        // don't generate local IDs if not needed
        assert(3 == numChannels); // if we do need local ids, we support only all 3 channels
        NEO::generateLocalIDs(perThreadDataForWholeThreadGroup, static_cast<uint16_t>(getSimdSize()),
                              std::array<uint16_t, 3>{{static_cast<uint16_t>(groupSizeX), static_cast<uint16_t>(groupSizeY), static_cast<uint16_t>(groupSizeZ)}},
                              std::array<uint8_t, 3>{{0, 1, 2}}, // to do : add support for non-default walk order
                              false);
    }

    this->groupSizeX = groupSizeX;
    this->groupSizeY = groupSizeY;
    this->groupSizeZ = groupSizeZ;

    auto simdSize = getKernelInfo()->getMaxSimdSize();
    this->threadsPerThreadGroup = static_cast<uint32_t>((itemsInGroup + simdSize - 1u) / simdSize);
    this->perThreadDataSize = perThreadDataSizeForWholeThreadGroup / threadsPerThreadGroup;
    patchWorkgroupSizeInCrossThreadData(groupSizeX, groupSizeY, groupSizeZ);

    // threadExecutionMask - which SIMD lines are active in last thread of group
    auto remainderSimdLanes = itemsInGroup & (simdSize - 1u);
    threadExecutionMask = (1ull << remainderSimdLanes) - 1u;
    if (!threadExecutionMask) {
        threadExecutionMask = ~threadExecutionMask;
    }

    return XE_RESULT_SUCCESS;
}

xe_result_t FunctionImp::suggestGroupSize(uint32_t globalSizeX,
                                          uint32_t globalSizeY,
                                          uint32_t globalSizeZ,
                                          uint32_t *groupSizeX,
                                          uint32_t *groupSizeY,
                                          uint32_t *groupSizeZ) {
    assert(0 != globalSizeX);
    assert(0 != globalSizeY);
    assert(0 != globalSizeZ);
    assert(nullptr != groupSizeX);
    assert(nullptr != groupSizeY);
    assert(nullptr != groupSizeZ);
    // TODO : unify this with NEO's computeWorkgroupSize
    // TODO : evaluate DebugManager.flags.EnableComputeWorkSizeND
    size_t retGroupSize[3] = {};
    auto maxWorkGroupSize = module->getMaxGroupSize();
    auto simd = getKernelInfo()->getMaxSimdSize();
    size_t workItems[3] = {globalSizeX, globalSizeY, globalSizeZ};
    uint32_t dim = 1U;
    if (globalSizeY > 1U) {
        dim = 2U;
    }
    if (globalSizeZ > 1U) {
        dim = 3U;
    }
    if (1U == dim) {
        NEO::computeWorkgroupSize1D(maxWorkGroupSize, retGroupSize, workItems, simd);
    } else if (NEO::DebugManager.flags.EnableComputeWorkSizeSquared.get() && (2U == dim)) {
        NEO::computeWorkgroupSizeSquared(maxWorkGroupSize, retGroupSize, workItems, simd, dim);
    } else {
        NEO::computeWorkgroupSize2D(maxWorkGroupSize, retGroupSize, workItems, simd);
    }

    *groupSizeX = static_cast<uint32_t>(retGroupSize[0]);
    *groupSizeY = static_cast<uint32_t>(retGroupSize[1]);
    *groupSizeZ = static_cast<uint32_t>(retGroupSize[2]);

    return XE_RESULT_SUCCESS;
}

xe_result_t FunctionImp::setArgImmediate(uint32_t argIndex, size_t argSize, const void *argVal) {
    assert(argVal != nullptr);
    const auto &kernelArgInfo = getKernelInfo()->kernelArgInfo[argIndex];
    DEBUG_BREAK_IF(kernelArgInfo.kernelArgPatchInfoVector.size() <= 0);

    //storeKernelArg(argIndex, NONE_OBJ, nullptr, nullptr, argSize);

    auto crossThreadDataEnd = ptrOffset(crossThreadData, getCrossThreadDataSize());

    for (const auto &kernelArgPatchInfo : kernelArgInfo.kernelArgPatchInfoVector) {
        DEBUG_BREAK_IF(kernelArgPatchInfo.size <= 0);
        auto pDst = ptrOffset(crossThreadData, kernelArgPatchInfo.crossthreadOffset);

        auto pSrc = ptrOffset(argVal, kernelArgPatchInfo.sourceOffset);

        DEBUG_BREAK_IF(!(ptrOffset(pDst, kernelArgPatchInfo.size) <= crossThreadDataEnd));
        ((void)(crossThreadDataEnd));

        if (kernelArgPatchInfo.sourceOffset < argSize) {
            size_t maxBytesToCopy = argSize - kernelArgPatchInfo.sourceOffset;
            size_t bytesToCopy = std::min(static_cast<size_t>(kernelArgPatchInfo.size), maxBytesToCopy);
            memcpy_s(pDst, kernelArgPatchInfo.size, pSrc, bytesToCopy);
        }
    }

    return XE_RESULT_SUCCESS;
}

xe_result_t FunctionImp::setArgBuffer(uint32_t argIndex, size_t argSize, const void *argVal) {
    const auto &kernelArgInfo = getKernelInfo()->kernelArgInfo[argIndex];

    auto patchLocation = ptrOffset(crossThreadData,
                                   kernelArgInfo.kernelArgPatchInfoVector[0].crossthreadOffset);

    patchWithRequiredSize(patchLocation, kernelArgInfo.kernelArgPatchInfoVector[0].size, *reinterpret_cast<const uintptr_t *>(argVal));

    GraphicsAllocation *alloc = module->getDevice()->getMemoryManager()->findAllocation(*reinterpret_cast<void *const *>(argVal));
    assert(alloc != nullptr); // TODO : Handle nullptr if *argVal == NULL

    oclInternals->storeKernelArg(argIndex, NEO::Kernel::BUFFER_OBJ, nullptr, argVal, argSize);

    // Handle stateles to stateful
    if (getKernelInfo()->requiresSshForBuffers) {
        setBufferSurfaceState(argIndex, *reinterpret_cast<void *const *>(argVal), alloc);
    }

    residencyContainer[argIndex] = alloc;

    return XE_RESULT_SUCCESS;
}

xe_result_t FunctionImp::setArgImage(uint32_t argIndex, size_t argSize, const void *argVal) {
    const auto image = Image::fromHandle(*static_cast<const xe_image_handle_t *>(argVal));
    const auto &kernelArgInfo = getKernelInfo()->kernelArgInfo[argIndex];

    oclInternals->storeKernelArg(argIndex, NEO::Kernel::IMAGE_OBJ, image, argVal, argSize);

    auto ssh = getSurfaceStateHeap();
    assert(ssh);

    //Optimization?  Rather than setting up and copying into a function's SSH, save references to the
    // arguments' surface states, then do all the copying and BTS updating once in appendLaunchFunction
    image->copySurfaceStateToSSH(ssh, kernelArgInfo.offsetHeap,
                                 static_cast<uint32_t>(oclInternals->localBindingTableOffset), kernelArgBindingTableIndex[argIndex]);

    GraphicsAllocation *alloc = image->getAllocation();
    assert(alloc);
    residencyContainer[argIndex] = alloc;

    return XE_RESULT_SUCCESS;
}

bool FunctionImp::initialize(const xe_function_desc_t *desc) {
    assert(desc->version == XE_API_HEADER_VERSION);
    assert(desc->flags == 0);

    this->immFuncInfo = module->getImmutableFunctionInfo(CStringRef(desc->pFunctionName));
    assert(this->immFuncInfo != nullptr);
    PtrRef<NEO::KernelInfo> kernelInfoRT = immFuncInfo->kernelInfoRT.weakRefReinterpret<NEO::KernelInfo>();
    assert(kernelInfoRT != nullptr);

    // TODO : move immutable kernelRT to ImmutableFunctionInfo
    // kernelRT is currently part of Function because in early stages of API, Function objects were immutable/singleton (thanks to separation from FunctionArgs)
    // right now Function is greatly mutable and mutli-instanced, that's why immutable resources should be moved to ImmutableFunctionInfo
    kernelRT = new NEO_temporary::LightweightOclKernel(static_cast<NEO::Program *>(static_cast<ModuleImp *>(module)->getProgramRT()), *kernelInfoRT);
    kernelRT->initialize();

    // clone muttables from kernel object - note some may be immutable - fix this later
    this->oclInternals->kernelArguments = kernelRT->kernelArguments;
    for (auto handleRT : kernelRT->kernelArgHandlers) {
        if (handleRT == &NEO::Kernel::setArgBuffer) {
            this->oclInternals->kernelArgHandlers.push_back(&FunctionImp::setArgBuffer);
        } else if (handleRT == &NEO::Kernel::setArgImage) {
            this->oclInternals->kernelArgHandlers.push_back(&FunctionImp::setArgImage);
        } else if (handleRT == &NEO::Kernel::setArgImmediate) {
            this->oclInternals->kernelArgHandlers.push_back(&FunctionImp::setArgImmediate);
        } else {
            assert(0);
        }
    }

    this->oclInternals->kernelSvmGfxAllocations = kernelRT->kernelSvmGfxAllocations;

    this->oclInternals->numberOfBindingTableStates = kernelRT->numberOfBindingTableStates;
    this->oclInternals->localBindingTableOffset = kernelRT->localBindingTableOffset;
    if (kernelRT->sshLocalSize != 0) {
        this->oclInternals->pSshLocal = std::make_unique<char[]>(kernelRT->sshLocalSize);
        // just copy-over ssh w/ binding table
        // note : binding table is already set-up properly by the compiler
        memcpy(this->oclInternals->pSshLocal.get(), kernelRT->pSshLocal.get(), kernelRT->sshLocalSize);
        this->oclInternals->sshLocalSize = kernelRT->sshLocalSize;

        //Precompute an array of kernel argument BTIs.
        auto &hwHelper = module->getDevice()->getHwHelper();

        uint32_t numArgs = static_cast<uint32_t>(kernelInfoRT->kernelArgInfo.size());
        kernelArgBindingTableIndex = new uint32_t[numArgs];
    }

    if (kernelRT->crossThreadDataSize != 0) {
        this->crossThreadData = new char[kernelRT->crossThreadDataSize];
        memcpy(this->crossThreadData, kernelRT->crossThreadData, kernelRT->crossThreadDataSize);
        this->crossThreadDataSize = kernelRT->crossThreadDataSize;
    }

    setGroupSize(getSimdSize(), 1, 1); // until apps sets-up something smarter

    residencyContainer.resize(this->oclInternals->kernelArgHandlers.size(), nullptr); // todo : handle implicit surfaces - printf/private/constant

    this->createPrintfBuffer();
    if (kernelRT->privateSurface != nullptr) {
        privateMemAllocation.rebind(new GraphicsAllocation(kernelRT->privateSurface));
        residencyContainer.push_back(privateMemAllocation.weakRef().get());
    }

    this->oclInternals->usingSharedObjArgs = kernelRT->usingSharedObjArgs;
    this->oclInternals->usingImagesOnly = kernelRT->usingImagesOnly;
    this->oclInternals->auxTranslationRequired = kernelRT->auxTranslationRequired;
    this->oclInternals->patchedArgumentsNum = kernelRT->patchedArgumentsNum;
    this->oclInternals->startOffset = kernelRT->startOffset;

    return true;
}

const void *FunctionImp::getIsaHostMem() const {
    return kernelRT->getKernelHeap();
}

size_t FunctionImp::getIsaSize() const {
    return kernelRT->getKernelHeapSize();
}

uint32_t FunctionImp::getSimdSize() const {
    return kernelRT->kernelInfo.getMaxSimdSize();
}

bool FunctionImp::getHasBarriers() const {
    return getKernelInfo()->patchInfo.executionEnvironment->HasBarriers;
}

uint32_t FunctionImp::getSlmSize() const {
    if (getKernelInfo()->patchInfo.localsurface) {
        return getKernelInfo()->patchInfo.localsurface->TotalInlineLocalMemorySize;
    }
    return 0;
}

bool FunctionImp::hasPrintfOutput() const {
    return getKernelInfo()->patchInfo.pAllocateStatelessPrintfSurface != nullptr;
}

void FunctionImp::createPrintfBuffer() {
    if (this->hasPrintfOutput()) {
        this->printfBuffer = PrintfHandler::createPrintfBuffer(this->module->getDevice());
        this->residencyContainer.push_back(printfBuffer);
        this->patchCrossThreadData(this->getKernelInfo()->patchInfo.pAllocateStatelessPrintfSurface->DataParamOffset,
                                   static_cast<uintptr_t>(this->printfBuffer->getGpuAddressOffsetFromHeapBase()));
    }
}

void FunctionImp::printPrintfOutput() {
    PrintfHandler::printOutput(this->kernelRT, this->printfBuffer);
}

//TODO for performance, make sure this is inlined
void *FunctionImp::getSurfaceStateHeap() const {
    return this->oclInternals->pSshLocal.get();
}

uint32_t FunctionImp::getSurfaceStateHeapSize() const {
    return this->oclInternals->sshLocalSize;
}

uint32_t FunctionImp::getBindingTableStateCount() const {
    return static_cast<uint32_t>(this->oclInternals->numberOfBindingTableStates);
}

uint32_t FunctionImp::getBindingTableOffset() const {
    return static_cast<uint32_t>(this->oclInternals->localBindingTableOffset);
}

const iOpenCL::SPatchSamplerStateArray *FunctionImp::getSamplerStateArray() const {
    return this->getKernelInfo()->patchInfo.samplerStateArray;
}

const void *FunctionImp::getDynamicStateHeap() const {
    return this->kernelRT->getDynamicStateHeap();
}

const size_t FunctionImp::getDynamicStateHeapSize() const {
    return this->kernelRT->getDynamicStateHeapSize();
}

template <typename T>
bool FunctionImp::patchCrossThreadData(uint32_t location, const T &value) {
    if (NEO::KernelArgInfo::undefinedOffset == location) {
        return false;
    }
    *reinterpret_cast<T *>(ptrOffset(this->crossThreadData, location)) = value;
    return true;
}

template bool FunctionImp::patchCrossThreadData<uint32_t>(uint32_t location, const uint32_t &value);
template bool FunctionImp::patchCrossThreadData<uint64_t>(uint32_t location, const uint64_t &value);
template bool FunctionImp::patchCrossThreadData<size_t>(uint32_t location, const size_t &value);
template bool FunctionImp::patchCrossThreadData<uintptr_t>(uint32_t location, const uintptr_t &value);

void FunctionImp::patchWorkgroupSizeInCrossThreadData(uint32_t x, uint32_t y, uint32_t z) {
    patchCrossThreadData(getKernelInfo()->workloadInfo.localWorkSizeOffsets[0], x);
    patchCrossThreadData(getKernelInfo()->workloadInfo.localWorkSizeOffsets[1], y);
    patchCrossThreadData(getKernelInfo()->workloadInfo.localWorkSizeOffsets[2], z);

    patchCrossThreadData(getKernelInfo()->workloadInfo.localWorkSizeOffsets2[0], x); // not sure why we have second set of those
    patchCrossThreadData(getKernelInfo()->workloadInfo.localWorkSizeOffsets2[1], y);
    patchCrossThreadData(getKernelInfo()->workloadInfo.localWorkSizeOffsets2[2], z);

    patchCrossThreadData(getKernelInfo()->workloadInfo.enqueuedLocalWorkSizeOffsets[0], x);
    patchCrossThreadData(getKernelInfo()->workloadInfo.enqueuedLocalWorkSizeOffsets[1], y);
    patchCrossThreadData(getKernelInfo()->workloadInfo.enqueuedLocalWorkSizeOffsets[2], z);
}

Function *Function::create(uint32_t productFamily, Module *module, const xe_function_desc_t *desc) {
    FunctionAllocatorFn allocator = nullptr;
    if (productFamily < IGFX_MAX_PRODUCT) {
        allocator = functionFactory[productFamily];
    }

    auto function = static_cast<FunctionImp *>(allocator(module));
    function->initialize(desc);
    return function;
}

} // namespace L0
