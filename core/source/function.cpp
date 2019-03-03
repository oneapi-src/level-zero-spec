#include "module_imp.h"

#include "device.h"
#include "memory_manager.h"

#include "runtime/context/context.h"
#include "runtime/helpers/basic_math.h"
#include "runtime/helpers/per_thread_data.h"
#include "runtime/kernel/kernel.h"
#include "runtime/program/kernel_arg_info.h"
#include "runtime/program/program.h"

#include <cassert>
#include <memory>

namespace OCLRT_temporary {
struct LightweightOclKernel : public OCLRT::Kernel {
    LightweightOclKernel(OCLRT::Program *program, const OCLRT::KernelInfo &kernelInfo)
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
} // namespace OCLRT_temporary

namespace OCLRT {
namespace Math {
using namespace ::Math; // just to emphasize the origin (wich originally is not encapsulated in OCLRT)
}
using KernelArgInfo = ::KernelArgInfo;
} // namespace OCLRT

namespace L0 {

struct FunctionImp : Function {
    FunctionImp(Module *module) : module(module) {}

    virtual ~FunctionImp() {
        alignedFree(perThreadData);
        kernelRT->release();
    }

    xe_result_t destroy() override {
        delete this;
        return XE_RESULT_SUCCESS;
    }

    xe_result_t setAttribute(xe_function_set_attribute_t attr,
                             uint32_t value) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t getAttribute(xe_function_get_attribute_t attr,
                             uint32_t *pValue) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    xe_result_t setArgumentValue(uint32_t argIndex,
                                 size_t argSize,
                                 const void *pArgValue) override {
        assert(argIndex < oclInternals.kernelArgHandlers.size());
        (this->*oclInternals.kernelArgHandlers[argIndex])(argIndex, argSize, pArgValue);
        return XE_RESULT_SUCCESS;
    }

    void setGroupCount(uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) override {
        uint32_t groupSizeX;
        uint32_t groupSizeY;
        uint32_t groupSizeZ;
        getGroupSize(groupSizeX, groupSizeY, groupSizeZ);

        const auto &kernelInfo = kernelRT->getKernelInfo();
        patchCrossThreadDataBasedOnKernelRT(kernelInfo.workloadInfo.globalWorkSizeOffsets[0], groupCountX * groupSizeX);
        patchCrossThreadDataBasedOnKernelRT(kernelInfo.workloadInfo.globalWorkSizeOffsets[1], groupCountY * groupSizeY);
        patchCrossThreadDataBasedOnKernelRT(kernelInfo.workloadInfo.globalWorkSizeOffsets[2], groupCountZ * groupSizeZ);
    }

    xe_result_t setGroupSize(uint32_t groupSizeX,
                             uint32_t groupSizeY,
                             uint32_t groupSizeZ) override {
        auto numChannels = OCLRT::PerThreadDataHelper::getNumLocalIdChannels(*kernelRT->kernelInfo.patchInfo.threadPayload);
        Vec3<size_t> groupSize{groupSizeX, groupSizeY, groupSizeZ};
        auto itemsInGroup = OCLRT::Math::computeTotalElementsCount(groupSize);
        size_t perThreadDataSizeNeeded = OCLRT::PerThreadDataHelper::getPerThreadDataSizeTotal(kernelRT->kernelInfo.getMaxSimdSize(), numChannels, itemsInGroup);
        if (perThreadDataSizeNeeded > perThreadDataSize) {
            alignedFree(perThreadData);
            perThreadData = alignedMalloc(perThreadDataSizeNeeded, 32); // alignment for vector instructions
            perThreadDataSize = perThreadDataSizeNeeded;
        }

        OCLRT::generateLocalIDs(perThreadData, static_cast<uint16_t>(getSimdSize()),
                                std::array<uint16_t, 3>{{static_cast<uint16_t>(groupSizeX), static_cast<uint16_t>(groupSizeY), static_cast<uint16_t>(groupSizeZ)}},
                                std::array<uint8_t, 3>{{0, 1, 2}}, // to do : add support for non-default walk order
                                false);

        this->groupSizeX = groupSizeX;
        this->groupSizeY = groupSizeY;
        this->groupSizeZ = groupSizeZ;

        auto simdSize = kernelRT->kernelInfo.getMaxSimdSize();
        this->threadsPerThreadGroup = static_cast<uint32_t>((itemsInGroup + simdSize - 1u) / simdSize);
        patchWorkgroupSizeInCrossThreadData(groupSizeX, groupSizeY, groupSizeZ);

        // threadExecutionMask - which SIMD lines are active in last thread of group
        auto remainderSimdLanes = itemsInGroup & (simdSize - 1u);
        threadExecutionMask = (1ull << remainderSimdLanes) - 1u;
        if (!threadExecutionMask) {
            threadExecutionMask = ~threadExecutionMask;
        }

        return XE_RESULT_SUCCESS;
    }

    xe_result_t suggestGroupSize(uint32_t globalSizeX,
                                 uint32_t globalSizeY,
                                 uint32_t globalSizeZ,
                                 uint32_t *groupSizeX,
                                 uint32_t *groupSizeY,
                                 uint32_t *groupSizeZ) override {
        return XE_RESULT_ERROR_UNSUPPORTED;
    }

    const void *getCrossThreadDataHostMem() const override {
        return crossThreadData;
    }

    size_t getCrossThreadDataSize() const override {
        return crossThreadDataSize;
    }

    const std::vector<GraphicsAllocation *> &getResidencyContainer() const override {
        return residencyContainer;
    }

    void getGroupSize(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY, uint32_t &outGroupSizeZ) const override {
        outGroupSizeX = this->groupSizeX;
        outGroupSizeY = this->groupSizeY;
        outGroupSizeZ = this->groupSizeZ;
    }

    xe_result_t setArgImmediate(uint32_t argIndex, size_t argSize, const void *argVal) {
        const auto &kernelArgInfo = kernelRT->getKernelInfo().kernelArgInfo[argIndex];
        auto patchLocation = ptrOffset(crossThreadData,
                                       kernelArgInfo.kernelArgPatchInfoVector[0].crossthreadOffset);

        patchWithRequiredSize(patchLocation, kernelArgInfo.kernelArgPatchInfoVector[0].size, *reinterpret_cast<const uintptr_t *>(argVal));

        //oclInternals.storeKernelArg(argIndex, OCLRT::Kernel::BUFFER_OBJ, nullptr, argVal, argSize);

        return XE_RESULT_SUCCESS;
    }

    xe_result_t setArgBuffer(uint32_t argIndex, size_t argSize, const void *argVal) {
        const auto &kernelArgInfo = kernelRT->getKernelInfo().kernelArgInfo[argIndex];
        // patchBufferOffset(kernelArgInfo, nullptr, nullptr); // stateless to stateful buffer offsets disabled

        auto patchLocation = ptrOffset(crossThreadData,
                                       kernelArgInfo.kernelArgPatchInfoVector[0].crossthreadOffset);

        patchWithRequiredSize(patchLocation, kernelArgInfo.kernelArgPatchInfoVector[0].size, *reinterpret_cast<const uintptr_t *>(argVal));

        oclInternals.storeKernelArg(argIndex, OCLRT::Kernel::BUFFER_OBJ, nullptr, argVal, argSize);

        //if (requiresSshForBuffers()) {
        //    auto surfaceState = ptrOffset(getSurfaceStateHeap(), kernelArgInfo.offsetHeap);
        //    Buffer::setSurfaceState(&getDevice(), surfaceState, 0, nullptr);
        //} // no SSH for buffers for now - stateless to stateful disabled

        GraphicsAllocation *alloc = module->getDevice()->getMemoryManager()->findAllocation(*reinterpret_cast<void *const *>(argVal));
        assert(alloc != nullptr);
        residencyContainer[argIndex] = alloc;

        return XE_RESULT_SUCCESS;
    }

    bool initialize(const xe_function_desc_t *desc) {
        assert(desc->version == XE_API_HEADER_VERSION);
        assert(desc->flags == 0);

        const OCLRT::KernelInfo *kernelInfoRT = static_cast<const OCLRT::KernelInfo *>(static_cast<ModuleImp *>(module)->getKernelInfoRT(desc->pFunctionName));
        assert(kernelInfoRT != nullptr);
        kernelRT = new OCLRT_temporary::LightweightOclKernel(static_cast<OCLRT::Program *>(static_cast<ModuleImp *>(module)->getProgramRT()), *kernelInfoRT);
        kernelRT->initialize();

        setGroupSize(getSimdSize(), 1, 1); // until apps sets-up something smarter

        // clone muttables from kernel object - note some may be immutable - fix this later
        this->oclInternals.kernelArguments = kernelRT->kernelArguments;
        for (auto handleRT : kernelRT->kernelArgHandlers) {
            if (handleRT == &OCLRT::Kernel::setArgBuffer) {
                this->oclInternals.kernelArgHandlers.push_back(&FunctionImp::setArgBuffer);
            } else if (handleRT == &OCLRT::Kernel::setArgImmediate) {
                this->oclInternals.kernelArgHandlers.push_back(&FunctionImp::setArgImmediate);
            } else {
                assert(0); // only setArgBuffer for now
            }
        }

        //Are these oclInternals.foo variables necessary? use kernelRT->foo instead.
        this->oclInternals.kernelSvmGfxAllocations = kernelRT->kernelSvmGfxAllocations;

        this->oclInternals.numberOfBindingTableStates = kernelRT->numberOfBindingTableStates;
        this->oclInternals.localBindingTableOffset = kernelRT->localBindingTableOffset;
        if (kernelRT->sshLocalSize != 0) {
            this->oclInternals.pSshLocal = std::make_unique<char[]>(kernelRT->sshLocalSize);
            memcpy(this->oclInternals.pSshLocal.get(), kernelRT->pSshLocal.get(), kernelRT->sshLocalSize);
            this->oclInternals.sshLocalSize = kernelRT->sshLocalSize;
        }

        if (kernelRT->crossThreadDataSize != 0) {
            this->crossThreadData = new char[kernelRT->crossThreadDataSize];
            memcpy(this->crossThreadData, kernelRT->crossThreadData, kernelRT->crossThreadDataSize);
            this->crossThreadDataSize = kernelRT->crossThreadDataSize;
        }

        this->oclInternals.usingSharedObjArgs = kernelRT->usingSharedObjArgs;
        this->oclInternals.usingImagesOnly = kernelRT->usingImagesOnly;
        this->oclInternals.auxTranslationRequired = kernelRT->auxTranslationRequired;
        this->oclInternals.patchedArgumentsNum = kernelRT->patchedArgumentsNum;
        this->oclInternals.startOffset = kernelRT->startOffset;
        residencyContainer.resize(this->oclInternals.kernelArgHandlers.size(), nullptr); // todo : handle implicit surfaces - printf/private/constant

        return true;
    }

    const void *getIsaHostMem() const override {
        return kernelRT->getKernelHeap();
    }

    size_t getIsaSize() const override {
        return kernelRT->getKernelHeapSize();
    }

    const void *getPerThreadDataHostMem() const override {
        return perThreadData;
    }

    size_t getPerThreadDataSize() const override {
        return perThreadDataSize;
    }

    uint32_t getSimdSize() const override {
        return kernelRT->kernelInfo.getMaxSimdSize();
    }

    uint32_t getThreadsPerThreadGroup() const override {
        return threadsPerThreadGroup;
    }

    uint32_t getThreadExecutionMask() const override {
        return threadExecutionMask;
    }

  protected:
    template <typename T>
    void patchCrossThreadDataBasedOnKernelRT(uint32_t location, const T &value) {
        if (OCLRT::KernelArgInfo::undefinedOffset == location) {
            return;
        }
        *reinterpret_cast<T *>(ptrOffset(kernelRT->crossThreadData, location)) = value;
    }

    void patchWorkgroupSizeInCrossThreadData(uint32_t x, uint32_t y, uint32_t z) {
        patchCrossThreadDataBasedOnKernelRT(kernelRT->kernelInfo.workloadInfo.localWorkSizeOffsets[0], x);
        patchCrossThreadDataBasedOnKernelRT(kernelRT->kernelInfo.workloadInfo.localWorkSizeOffsets[1], y);
        patchCrossThreadDataBasedOnKernelRT(kernelRT->kernelInfo.workloadInfo.localWorkSizeOffsets[2], z);

        patchCrossThreadDataBasedOnKernelRT(kernelRT->kernelInfo.workloadInfo.localWorkSizeOffsets2[0], x); // not sure why we have second set of those
        patchCrossThreadDataBasedOnKernelRT(kernelRT->kernelInfo.workloadInfo.localWorkSizeOffsets2[1], y);
        patchCrossThreadDataBasedOnKernelRT(kernelRT->kernelInfo.workloadInfo.localWorkSizeOffsets2[2], z);

        patchCrossThreadDataBasedOnKernelRT(kernelRT->kernelInfo.workloadInfo.enqueuedLocalWorkSizeOffsets[0], x);
        patchCrossThreadDataBasedOnKernelRT(kernelRT->kernelInfo.workloadInfo.enqueuedLocalWorkSizeOffsets[1], y);
        patchCrossThreadDataBasedOnKernelRT(kernelRT->kernelInfo.workloadInfo.enqueuedLocalWorkSizeOffsets[2], z);
    }

    typedef xe_result_t (FunctionImp::*FunctionArgHandler)(uint32_t argIndex, size_t argSize, const void *argVal);

    struct OCLInternal { // cloned from OCLRT::Kernel - keeping types/names the same for simplicity
        std::vector<OCLRT::Kernel::SimpleKernelArgInfo> kernelArguments;
        std::vector<FunctionImp::FunctionArgHandler> kernelArgHandlers;
        std::vector<OCLRT::GraphicsAllocation *> kernelSvmGfxAllocations;

        void storeKernelArg(uint32_t argIndex, OCLRT::Kernel::kernelArgType argType, void *argObject,
                            const void *argValue, size_t argSize,
                            OCLRT::GraphicsAllocation *argSvmAlloc = nullptr, cl_mem_flags argSvmFlags = 0) {
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
    } oclInternals;

    OCLRT_temporary::LightweightOclKernel *kernelRT = nullptr;
    Module *module = nullptr;

    std::vector<GraphicsAllocation *> residencyContainer;

    uint32_t groupSizeX = 0u;
    uint32_t groupSizeY = 0u;
    uint32_t groupSizeZ = 0u;

    char *crossThreadData = 0;
    uint32_t crossThreadDataSize = 0;

    void *perThreadData = nullptr;
    size_t perThreadDataSize = 0u;

    uint32_t threadsPerThreadGroup = 0u;
    uint32_t threadExecutionMask = 0u;
};

Function *Function::create(Module *module, const xe_function_desc_t *desc) {
    auto function = new FunctionImp(module);
    function->initialize(desc);
    return function;
}

} // namespace L0
