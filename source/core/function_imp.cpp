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

namespace NEO {
namespace Math {
using namespace ::Math; // just to emphasize the origin (wich originally is not encapsulated in
                        // OCLRT)
}
using KernelArgInfo = ::KernelArgInfo;
} // namespace NEO

namespace L0 {

FunctionImmutableData::~FunctionImmutableData() { isaGraphicsAllocation.deleteOwned(); }

template <typename PatchTokenT>
static void
patchWithImplicitSurface(PtrRef<uint8_t[]> crossThreadData, uint32_t crossThreadDataSize,
                         PtrRef<uint8_t[]> surfaceStateHeap, uint32_t surfaceStateHeapSize,
                         uintptr_t ptrToPatchInCrossThreadData, GraphicsAllocation &allocation,
                         const PatchTokenT &patch, const NEO::Device &deviceRT) {
    uint32_t pointerSize = patch.DataParamSize;

    if (crossThreadData != nullptr) {
        uint32_t crossThreadDataOffset = patch.DataParamOffset;
        FunctionSignature::patchPointer(
            crossThreadData, crossThreadDataSize,
            ArgPointer::onlyStateless(crossThreadDataOffset, pointerSize),
            ptrToPatchInCrossThreadData);
    }

    if (surfaceStateHeap != nullptr) {
        uint32_t sshOffset = patch.SurfaceStateHeapOffset;
        assert(sshOffset + 64 < surfaceStateHeapSize);
        auto surfaceState = surfaceStateHeap.weakRef().offsetBytesBy(sshOffset);
        void *addressToPatch = reinterpret_cast<void *>(allocation.getHostAddress());
        size_t sizeToPatch = allocation.getSize();
        NEO::Buffer::setSurfaceState(&deviceRT, surfaceState.get(), sizeToPatch, addressToPatch,
                                     allocation.allocationRT, 0);
    }
}

void FunctionImmutableData::initialize(PtrRef<void> kernelInfoRT, MemoryManager &memoryManager,
                                       const void *deviceRT, uint32_t computeUnitsUsedForSratch,
                                       PtrRef<GraphicsAllocation> globalConstBuffer,
                                       PtrRef<GraphicsAllocation> globalVarBuffer) {
    assert(kernelInfoRT != nullptr);
    this->kernelInfoRT = kernelInfoRT;
    auto &kernelInfo = *kernelInfoRT.weakRef<NEO::KernelInfo>();

    const auto &workloadInfo = kernelInfo.workloadInfo;
    const auto &patchInfo = kernelInfo.patchInfo;

    auto kernelIsaSize = kernelInfo.heapInfo.pKernelHeader->KernelHeapSize;
    isaGraphicsAllocation = memoryManager.allocateGraphicsMemoryForIsa(
        bindPtrRef(kernelInfo.heapInfo.pKernelHeap), kernelIsaSize);

    this->crossThreadDataSize =
        patchInfo.dataParameterStream ? patchInfo.dataParameterStream->DataParameterStreamSize : 0;

    if (crossThreadDataSize != 0) {
        crossThreadDataTemplate.rebind(new uint8_t[crossThreadDataSize], crossThreadDataSize);

        if (kernelInfo.crossThreadData) {
            memcpy_s(crossThreadDataTemplate.weakRef().get(), crossThreadDataSize,
                     kernelInfo.crossThreadData, crossThreadDataSize);
        } else {
            memset(crossThreadDataTemplate.weakRef().get(), 0x00, crossThreadDataSize);
        }

        static_assert(NEO::KernelArgInfo::undefinedOffset == Undefined, "");
        FunctionSignature::setOffsetsVec(this->signature.dispatchMetadata.globalWorkOffset,
                                         workloadInfo.globalWorkOffsetOffsets);
        FunctionSignature::setOffsetsVec(this->signature.dispatchMetadata.localWorkSize,
                                         workloadInfo.localWorkSizeOffsets);
        FunctionSignature::setOffsetsVec(this->signature.dispatchMetadata.localWorkSize2,
                                         workloadInfo.localWorkSizeOffsets2);
        FunctionSignature::setOffsetsVec(this->signature.dispatchMetadata.globalWorkSize,
                                         workloadInfo.globalWorkSizeOffsets);
        FunctionSignature::setOffsetsVec(this->signature.dispatchMetadata.enqueuedLocalWorkSize,
                                         workloadInfo.enqueuedLocalWorkSizeOffsets);
        FunctionSignature::setOffsetsVec(this->signature.dispatchMetadata.numWorkGroups,
                                         workloadInfo.numWorkGroupsOffset);

        this->signature.dispatchMetadata.workDim = workloadInfo.workDimOffset;

        if (kernelInfo.patchInfo.pAllocateStatelessPrintfSurface != nullptr) {
            this->signature.implicitArgs.printfSurface.stateless =
                kernelInfo.patchInfo.pAllocateStatelessPrintfSurface->DataParamOffset;
            this->signature.implicitArgs.printfSurface.pointerSize =
                kernelInfo.patchInfo.pAllocateStatelessPrintfSurface->DataParamSize;
            this->signature.implicitArgs.printfSurface.stateful =
                kernelInfo.patchInfo.pAllocateStatelessPrintfSurface->SurfaceStateHeapOffset;
            this->signature.attributes.flags.hasPrintf = true;
        }

        FunctionSignature::patchNonPointer<uint32_t>(
            this->crossThreadDataTemplate.weakRef(), this->crossThreadDataSize,
            workloadInfo.simdSizeOffset, kernelInfo.getMaxSimdSize());
    }

    // patch crossthread data and ssh with inline surfaces, if necessary
    uint32_t privateSurfaceSize = 0;
    if (patchInfo.pAllocateStatelessPrivateSurface != nullptr) {
        privateSurfaceSize = patchInfo.pAllocateStatelessPrivateSurface->PerThreadPrivateMemorySize;
    }

    if (privateSurfaceSize != 0) {
        privateSurfaceSize *= computeUnitsUsedForSratch * kernelInfo.getMaxSimdSize();
        assert(privateSurfaceSize != 0);

        this->privateMemoryGraphicsAllocation =
            memoryManager.allocateGraphicsMemoryForPrivateMemory(privateSurfaceSize);

        assert(this->privateMemoryGraphicsAllocation != nullptr);
        const auto &patchToken = patchInfo.pAllocateStatelessPrivateSurface;
        patchWithImplicitSurface(
            crossThreadDataTemplate.weakRef(), getCrossThreadDataSize(),
            bindPtrRef<uint8_t[]>(static_cast<uint8_t *>(kernelInfo.heapInfo.pSsh)),
            getSurfaceStateHeapSize(),
            static_cast<uintptr_t>(
                privateMemoryGraphicsAllocation->getGpuAddressOffsetFromHeapBase()),
            *privateMemoryGraphicsAllocation, *patchToken,
            *static_cast<const NEO::Device *>(deviceRT));
        this->residencyContainer.push_back(this->privateMemoryGraphicsAllocation.weakRef());
    }

    if (patchInfo.pAllocateStatelessConstantMemorySurfaceWithInitialization) {
        assert(globalConstBuffer != nullptr);

        const auto &patchToken =
            patchInfo.pAllocateStatelessConstantMemorySurfaceWithInitialization;
        patchWithImplicitSurface(
            crossThreadDataTemplate.weakRef(), getCrossThreadDataSize(),
            bindPtrRef<uint8_t[]>(static_cast<uint8_t *>(kernelInfo.heapInfo.pSsh)),
            getSurfaceStateHeapSize(),
            static_cast<uintptr_t>(globalConstBuffer->getGpuAddressOffsetFromHeapBase()),
            *globalConstBuffer, *patchToken, *static_cast<const NEO::Device *>(deviceRT));
        this->residencyContainer.push_back(globalConstBuffer.weakRef());
    }

    if (patchInfo.pAllocateStatelessGlobalMemorySurfaceWithInitialization) {
        assert(globalVarBuffer != nullptr);

        const auto &patchToken = patchInfo.pAllocateStatelessGlobalMemorySurfaceWithInitialization;
        patchWithImplicitSurface(
            crossThreadDataTemplate.weakRef(), getCrossThreadDataSize(),
            bindPtrRef<uint8_t[]>(static_cast<uint8_t *>(kernelInfo.heapInfo.pSsh)),
            getSurfaceStateHeapSize(),
            static_cast<uintptr_t>(globalVarBuffer->getGpuAddressOffsetFromHeapBase()),
            *globalVarBuffer, *patchToken, *static_cast<const NEO::Device *>(deviceRT));
        this->residencyContainer.push_back(globalVarBuffer.weakRef());
    }

    auto numArgs = kernelInfo.kernelArgInfo.size();
    this->signature.explicitArgs.args.reserve(numArgs);

    for (uint32_t i = 0; i < numArgs; ++i) {
        auto &argInfo = kernelInfo.kernelArgInfo[i];
        PtrOwn<Arg> argDesc;
        if ((argInfo.typeStr.find("*") != std::string::npos) || argInfo.isBuffer) {
            argDesc.rebind(new ArgPointer);
            auto &argPointer = argDesc->as<ArgPointer>();
            argPointer.stateful = argInfo.offsetHeap;
            assert(argInfo.kernelArgPatchInfoVector.size() == 1);
            argPointer.stateless = argInfo.kernelArgPatchInfoVector[0].crossthreadOffset;
            argPointer.pointerSize = argInfo.kernelArgPatchInfoVector[0].size;
            // TODO : Check bindless path
        } else if (argInfo.isImage) {
            argDesc.rebind(new ArgImage);
            auto &argImage = argDesc->as<ArgImage>();
            argImage.stateful = argInfo.offsetHeap;
            assert(argInfo.kernelArgPatchInfoVector.size() == 1);
            argImage.bindless = argInfo.kernelArgPatchInfoVector[0].crossthreadOffset;
            // TODO : Check bindless path

            argImage.metadata.arraySize = argInfo.offsetArraySize;
            argImage.metadata.channelDataType = argInfo.offsetChannelDataType;
            argImage.metadata.channelOrder = argInfo.offsetChannelOrder;
            argImage.metadata.imgDepth = argInfo.offsetImgDepth;
            argImage.metadata.imgHeight = argInfo.offsetImgHeight;
            argImage.metadata.imgWidth = argInfo.offsetImgWidth;
            argImage.metadata.numMipLevels = argInfo.offsetNumMipLevels;
            argImage.metadata.numSamples = argInfo.offsetNumSamples;
            argImage.metadata.samplerAddressingMode = argInfo.offsetSamplerAddressingMode;
            argImage.metadata.samplerNormalizedCoords = argInfo.offsetSamplerNormalizedCoords;
            argImage.metadata.samplerSnapWa = argInfo.offsetSamplerSnapWa;
        } else if (argInfo.isSampler) {
            argDesc.rebind(new Arg(Arg::ArgTSampler));
        } else {
            argDesc.rebind(new ArgValue);
            auto &argVal = argDesc->as<ArgValue>();
            argVal.elements.reserve(argInfo.kernelArgPatchInfoVector.size());

            for (const auto &patch : argInfo.kernelArgPatchInfoVector) {
                ArgValue::Element el;
                el.size = patch.size;
                el.sourceOffset = patch.sourceOffset;
                el.valueOffset = patch.crossthreadOffset;
                argVal.elements.push_back(el);
            }
        }
        this->signature.explicitArgs.args.push_back(std::move(argDesc));
    }

    signature.attributes.numLocalIdChannels =
        NEO::PerThreadDataHelper::getNumLocalIdChannels(*kernelInfo.patchInfo.threadPayload);
    signature.attributes.simdSize = kernelInfo.getMaxSimdSize();
    signature.attributes.slmInlineSize =
        kernelInfo.patchInfo.localsurface
            ? kernelInfo.patchInfo.localsurface->TotalInlineLocalMemorySize
            : 0;

    signature.attributes.flags.hasBarriers = kernelInfo.patchInfo.executionEnvironment->HasBarriers;
    signature.bindingTable.numSurfaceStates =
        kernelInfo.patchInfo.bindingTableState ? kernelInfo.patchInfo.bindingTableState->Count : 0;

    signature.bindingTable.tableOffset =
        kernelInfo.patchInfo.bindingTableState ? kernelInfo.patchInfo.bindingTableState->Offset : 0;

    if (kernelInfo.patchInfo.samplerStateArray != nullptr) {
        signature.samplerTable.tableOffset = kernelInfo.patchInfo.samplerStateArray->Offset;
        signature.samplerTable.numSamplers = kernelInfo.patchInfo.samplerStateArray->Count;
        signature.samplerTable.borderColor =
            kernelInfo.patchInfo.samplerStateArray->BorderColorOffset;
    }

    signature.name = kernelInfo.name;
}

uint32_t FunctionImmutableData::getIsaSize() const {
    return static_cast<uint32_t>(isaGraphicsAllocation->getSize());
}

uint64_t FunctionImmutableData::getPrivateMemorySize() const {
    uint64_t size = 0;
    if (privateMemoryGraphicsAllocation != nullptr) {
        size = privateMemoryGraphicsAllocation->getSize();
    }
    return size;
}

uint32_t FunctionImmutableData::getSurfaceStateHeapSize() const {
    auto &kernelInfo = *kernelInfoRT.weakRef<NEO::KernelInfo>();
    return kernelInfo.heapInfo.pKernelHeader->SurfaceStateHeapSize;
}

PtrRef<const uint8_t[]> FunctionImmutableData::getSurfaceStateHeapTemplate() const {
    auto &kernelInfo = *kernelInfoRT.weakRef<NEO::KernelInfo>();
    return bindPtrRef<const uint8_t[]>(static_cast<uint8_t *>(kernelInfo.heapInfo.pSsh));
}

uint32_t FunctionImmutableData::getDynamicStateHeapDataSize() const {
    auto &kernelInfo = *kernelInfoRT.weakRef<NEO::KernelInfo>();
    return kernelInfo.heapInfo.pKernelHeader->DynamicStateHeapSize;
}

PtrRef<const uint8_t[]> FunctionImmutableData::getDynamicStateHeapTemplate() const {
    auto &kernelInfo = *kernelInfoRT.weakRef<NEO::KernelInfo>();
    return bindPtrRef<const uint8_t[]>(static_cast<const uint8_t *>(kernelInfo.heapInfo.pDsh));
}

FunctionImp::FunctionImp(Module *module) : module(module) {}

FunctionImp::~FunctionImp() {
    if (perThreadDataForWholeThreadGroup != nullptr) {
        alignedFree(perThreadDataForWholeThreadGroup.weakRef().get()); // TODO : Refactor this
        perThreadDataForWholeThreadGroup.rebind(nullptr);
    }
    if (printfBuffer != nullptr) {
        globalMemoryManager->freeMemory(printfBuffer.weakRef().get());
    }
    crossThreadData.deleteOwned();
    surfaceStateHeapData.deleteOwned();
    dynamicStateHeapData.deleteOwned();
}

xe_result_t FunctionImp::setArgumentValue(uint32_t argIndex, size_t argSize,
                                          const void *pArgValue) {
    assert(argIndex < kernelArgHandlers.size());
    (this->*kernelArgHandlers[argIndex])(argIndex, argSize, pArgValue);
    return XE_RESULT_SUCCESS;
}

void FunctionImp::setGroupCount(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
    uint32_t groupSizeX;
    uint32_t groupSizeY;
    uint32_t groupSizeZ;
    getGroupSize(groupSizeX, groupSizeY, groupSizeZ);

    const FunctionSignature &sig = funcImmData->getSignature();
    uint32_t globalWorkSize[3] = {groupCountX * groupSizeX, groupCountY * groupSizeY,
                                  groupCountZ * groupSizeZ};
    FunctionSignature::patchVecNonPointer(crossThreadData.weakRef(), crossThreadDataSize,
                                          sig.dispatchMetadata.globalWorkSize, globalWorkSize);

    uint32_t groupCount[3] = {groupCountX, groupCountY, groupCountZ};
    FunctionSignature::patchVecNonPointer(crossThreadData.weakRef(), crossThreadDataSize,
                                          sig.dispatchMetadata.numWorkGroups, groupCount);
}

xe_result_t FunctionImp::setGroupSize(uint32_t groupSizeX, uint32_t groupSizeY,
                                      uint32_t groupSizeZ) {
    if ((0 == groupSizeX) || (0 == groupSizeY) || (0 == groupSizeZ)) {
        return XE_RESULT_ERROR_INVALID_PARAMETER; // needs clarification in the spec
    }

    auto numChannels = funcImmData->getSignature().attributes.numLocalIdChannels;
    Vec3<size_t> groupSize{groupSizeX, groupSizeY, groupSizeZ};
    auto itemsInGroup = NEO::Math::computeTotalElementsCount(groupSize);
    uint32_t perThreadDataSizeForWholeThreadGroupNeeded =
        static_cast<uint32_t>(NEO::PerThreadDataHelper::getPerThreadDataSizeTotal(
            funcImmData->getSignature().attributes.simdSize, numChannels, itemsInGroup));
    if (perThreadDataSizeForWholeThreadGroupNeeded >
        perThreadDataSizeForWholeThreadGroupAllocated) {
        alignedFree(perThreadDataForWholeThreadGroup.weakRef().get());
        perThreadDataForWholeThreadGroup.rebind(static_cast<uint8_t *>(alignedMalloc(
            perThreadDataSizeForWholeThreadGroupNeeded, 32))); // alignment for vector instructions
        perThreadDataSizeForWholeThreadGroupAllocated = perThreadDataSizeForWholeThreadGroupNeeded;
    }
    perThreadDataSizeForWholeThreadGroup = perThreadDataSizeForWholeThreadGroupNeeded;

    if (numChannels > 0) {
        // don't generate local IDs if not needed
        assert(3 == numChannels); // if we do need local ids, we support only all 3 channels
        NEO::generateLocalIDs(
            perThreadDataForWholeThreadGroup.weakRef().get(),
            static_cast<uint16_t>(funcImmData->getSignature().attributes.simdSize),
            std::array<uint16_t, 3>{{static_cast<uint16_t>(groupSizeX),
                                     static_cast<uint16_t>(groupSizeY),
                                     static_cast<uint16_t>(groupSizeZ)}},
            std::array<uint8_t, 3>{{0, 1, 2}}, // to do : add support for non-default walk order
            false);
    }

    this->groupSize[0] = groupSizeX;
    this->groupSize[1] = groupSizeY;
    this->groupSize[2] = groupSizeZ;

    auto simdSize = funcImmData->getSignature().attributes.simdSize;
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

xe_result_t FunctionImp::suggestGroupSize(uint32_t globalSizeX, uint32_t globalSizeY,
                                          uint32_t globalSizeZ, uint32_t *groupSizeX,
                                          uint32_t *groupSizeY, uint32_t *groupSizeZ) {
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
    auto simd = funcImmData->getSignature().attributes.simdSize;
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
    assert(funcImmData->getSignature().explicitArgs.args.size() > argIndex);
    const auto &arg = funcImmData->getSignature().explicitArgs.args[argIndex];

    for (const auto &element : arg->as<ArgValue>().elements) {
        auto pDst = crossThreadData.weakRef().offsetBytesBy(element.valueOffset);
        auto pSrc = ptrOffset(argVal, element.sourceOffset);

        if (element.sourceOffset < argSize) {
            size_t maxBytesToCopy = argSize - element.sourceOffset;
            size_t bytesToCopy = std::min(static_cast<size_t>(element.size), maxBytesToCopy);
            memcpy_s(pDst.get(), element.size, pSrc, bytesToCopy);
        }
    }
    return XE_RESULT_SUCCESS;
}

xe_result_t FunctionImp::setArgBuffer(uint32_t argIndex, size_t argSize, const void *argVal) {
    const auto &arg = funcImmData->getSignature().explicitArgs.args[argIndex]->as<ArgPointer>();
    const auto val = *reinterpret_cast<const uintptr_t *>(argVal);

    FunctionSignature::patchPointer(crossThreadData.weakRef(), crossThreadDataSize, arg, val);

    GraphicsAllocation *alloc =
        globalMemoryManager->findGraphicsAllocation(*reinterpret_cast<void *const *>(argVal));
    assert(alloc != nullptr); // TODO : Handle nullptr if *argVal == NULL

    // Handle stateles to stateful
    setBufferSurfaceState(argIndex, *reinterpret_cast<void *const *>(argVal), alloc);

    residencyContainer[argIndex] = alloc;

    return XE_RESULT_SUCCESS;
}

xe_result_t FunctionImp::setArgImage(uint32_t argIndex, size_t argSize, const void *argVal) {
    const auto image = Image::fromHandle(*static_cast<const xe_image_handle_t *>(argVal));
    const auto &arg = funcImmData->getSignature().explicitArgs.args[argIndex]->as<ArgImage>();

    assert(surfaceStateHeapData != nullptr);

    // Optimization?  Rather than setting up and copying into a function's SSH, save references to
    // the
    // arguments' surface states, then do all the copying and BTS updating once in
    // appendLaunchFunction
    image->copySurfaceStateToSSH(surfaceStateHeapData.weakRef().get(), arg.stateful);

    GraphicsAllocation *alloc = image->getAllocation();
    assert(alloc);
    residencyContainer[argIndex] = alloc;

    return XE_RESULT_SUCCESS;
}

bool FunctionImp::initialize(const xe_function_desc_t *desc) {
    assert(desc->version == XE_API_HEADER_VERSION);
    assert(desc->flags == 0);

    this->funcImmData = module->getFunctionImmutableData(CStringRef(desc->pFunctionName));
    assert(this->funcImmData != nullptr);

    for (const auto &argT : funcImmData->getSignature().explicitArgs.args) {
        switch (argT->type) {
        case Arg::ArgTPointer:
            this->kernelArgHandlers.push_back(&FunctionImp::setArgBuffer);
            break;
        case Arg::ArgTImage:
            this->kernelArgHandlers.push_back(&FunctionImp::setArgImage);
            break;
        case Arg::ArgTSampler:
            assert(0);
            this->kernelArgHandlers.push_back(&FunctionImp::setArgImmediate);
            break;
        case Arg::ArgTValue:
            this->kernelArgHandlers.push_back(&FunctionImp::setArgImmediate);
            break;
        }
    }

    if (funcImmData->getSurfaceStateHeapSize() > 0) {
        this->surfaceStateHeapData.rebind(new uint8_t[funcImmData->getSurfaceStateHeapSize()],
                                          funcImmData->getSurfaceStateHeapSize());
        memcpy(this->surfaceStateHeapData.weakRef().get(),
               funcImmData->getSurfaceStateHeapTemplate().get(),
               funcImmData->getSurfaceStateHeapSize());
        this->surfaceStateHeapDataSize = funcImmData->getSurfaceStateHeapSize();
    }

    if (funcImmData->getCrossThreadDataSize() != 0) {
        this->crossThreadData.rebind(new uint8_t[funcImmData->getCrossThreadDataSize()],
                                     funcImmData->getCrossThreadDataSize());
        memcpy(this->crossThreadData.weakRef().get(),
               funcImmData->getCrossThreadDataTemplate().get(),
               funcImmData->getCrossThreadDataSize());
        this->crossThreadDataSize = funcImmData->getCrossThreadDataSize();
    }

    if (funcImmData->getDynamicStateHeapDataSize() != 0) {
        this->dynamicStateHeapData.rebind(new uint8_t[funcImmData->getDynamicStateHeapDataSize()],
                                          funcImmData->getDynamicStateHeapDataSize());
        memcpy(this->dynamicStateHeapData.weakRef().get(),
               funcImmData->getDynamicStateHeapTemplate().get(),
               funcImmData->getDynamicStateHeapDataSize());
        this->dynamicStateHeapDataSize = funcImmData->getDynamicStateHeapDataSize();
    }

    // TODO : reqd_workgroup_size
    // TODO : fused EUs
    setGroupSize(funcImmData->getSignature().attributes.simdSize, 1,
                 1); // until apps chooses something smarter

    residencyContainer.resize(this->kernelArgHandlers.size(), nullptr);

    this->createPrintfBuffer();

    for (auto &alloc : funcImmData->getResidencyContainer()) {
        residencyContainer.push_back(alloc.get());
    }

    return true;
}

void FunctionImp::createPrintfBuffer() {
    if (this->funcImmData->getSignature().attributes.flags.hasPrintf) {
        this->printfBuffer.rebind(PrintfHandler::createPrintfBuffer(this->module->getDevice()));
        this->residencyContainer.push_back(printfBuffer.weakRef().get());
        FunctionSignature::patchPointer(
            crossThreadData.weakRef(), crossThreadDataSize,
            this->getImmutableData()->getSignature().implicitArgs.printfSurface,
            static_cast<uintptr_t>(this->printfBuffer->getGpuAddressOffsetFromHeapBase()));
    }
}

void FunctionImp::printPrintfOutput() {
    PrintfHandler::printOutput(funcImmData, this->printfBuffer.weakRef(), module->getDevice());
}

void FunctionImp::patchWorkgroupSizeInCrossThreadData(uint32_t x, uint32_t y, uint32_t z) {
    const FunctionSignature &sig = funcImmData->getSignature();
    uint32_t workgroupSize[3] = {x, y, z};
    FunctionSignature::patchVecNonPointer(crossThreadData.weakRef(), crossThreadDataSize,
                                          sig.dispatchMetadata.localWorkSize, workgroupSize);
    FunctionSignature::patchVecNonPointer(
        crossThreadData.weakRef(), crossThreadDataSize, sig.dispatchMetadata.localWorkSize2,
        workgroupSize); // not sure why we have second set of those
    FunctionSignature::patchVecNonPointer(crossThreadData.weakRef(), crossThreadDataSize,
                                          sig.dispatchMetadata.enqueuedLocalWorkSize,
                                          workgroupSize);
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
