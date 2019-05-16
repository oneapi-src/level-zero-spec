#pragma once
#include "xe_common.h"
#include "xe_module.h"

#include "ptr.h"

#include <string>
#include <vector>

namespace iOpenCL {
struct SPatchSamplerStateArray;
} // namespace iOpenCL

struct _xe_function_handle_t {};

namespace L0 {
struct GraphicsAllocation;
struct MemoryManager;
struct Module;

using CrossThreadDataOffset = uint32_t;
using DynamicStateHeapOffset = uint32_t;
using SurfaceStateHeapOffset = uint32_t;
constexpr CrossThreadDataOffset Undefined = 0xFFFFFFFF;

struct Arg {
    enum ArgType : uint8_t { ArgTPointer, ArgTImage, ArgTSampler, ArgTValue };

    Arg(ArgType type) : type(type) {}

    template <typename T> const T &as() const;

    template <typename T> T &as();

    const ArgType type;
};

struct ArgPointer : Arg {
    ArgPointer() : Arg(ArgTPointer) {}
    static ArgPointer onlyStateless(CrossThreadDataOffset offset, uint32_t pointerSize) {
        ArgPointer arg;
        arg.stateless = offset;
        arg.pointerSize = pointerSize;
        return arg;
    }
    CrossThreadDataOffset stateless = Undefined;
    CrossThreadDataOffset bindless = Undefined;
    SurfaceStateHeapOffset stateful = Undefined;

    uint32_t pointerSize = 0;

    CrossThreadDataOffset bufferOffset = Undefined;
};

struct ArgImage : Arg {
    ArgImage() : Arg(ArgTImage) {}

    CrossThreadDataOffset bindless = Undefined;
    SurfaceStateHeapOffset stateful = Undefined;
    struct {
        CrossThreadDataOffset imgWidth = Undefined;
        CrossThreadDataOffset imgHeight = Undefined;
        CrossThreadDataOffset imgDepth = Undefined;
        CrossThreadDataOffset channelDataType = Undefined;
        CrossThreadDataOffset channelOrder = Undefined;
        CrossThreadDataOffset arraySize = Undefined;
        CrossThreadDataOffset numSamples = Undefined;
        CrossThreadDataOffset samplerSnapWa = Undefined;
        CrossThreadDataOffset samplerAddressingMode = Undefined;
        CrossThreadDataOffset samplerNormalizedCoords = Undefined;
        CrossThreadDataOffset numMipLevels = Undefined;
    } metadata;
};

struct ArgValue : Arg {
    ArgValue() : Arg(ArgTValue) {}

    struct Element {
        CrossThreadDataOffset valueOffset = Undefined;
        uint32_t size = 0;
        uint32_t sourceOffset = 0;
    };
    std::vector<Element> elements;
};

template <> inline const ArgPointer &Arg::as<ArgPointer>() const {
    assert(type == ArgTPointer);
    return static_cast<const ArgPointer &>(*this);
}

template <> inline const ArgImage &Arg::as<ArgImage>() const {
    assert(type == ArgTImage);
    return static_cast<const ArgImage &>(*this);
}

template <> inline const ArgValue &Arg::as<ArgValue>() const {
    assert(type == ArgTValue);
    return static_cast<const ArgValue &>(*this);
}

template <> inline ArgPointer &Arg::as<ArgPointer>() {
    assert(type == ArgTPointer);
    return static_cast<ArgPointer &>(*this);
}

template <> inline ArgImage &Arg::as<ArgImage>() {
    assert(type == ArgTImage);
    return static_cast<ArgImage &>(*this);
}

template <> inline ArgValue &Arg::as<ArgValue>() {
    assert(type == ArgTValue);
    return static_cast<ArgValue &>(*this);
}

struct FunctionSignature {
    enum BufferAddressingMode : uint32_t { Stateless, StatefulAndStateless, BindlessAndStateless };
    enum ImageAddressingMode : uint32_t { Stateful, Bindless };

    FunctionSignature() = default;
    ~FunctionSignature() { deleteAllOwned(explicitArgs.args); }

    std::string name;

    struct {
        CrossThreadDataOffset globalWorkOffset[3] = {Undefined, Undefined, Undefined};
        CrossThreadDataOffset localWorkSize[3] = {Undefined, Undefined, Undefined};
        CrossThreadDataOffset localWorkSize2[3] = {Undefined, Undefined, Undefined};
        CrossThreadDataOffset globalWorkSize[3] = {Undefined, Undefined, Undefined};
        CrossThreadDataOffset enqueuedLocalWorkSize[3] = {Undefined, Undefined, Undefined};
        CrossThreadDataOffset numWorkGroups[3] = {Undefined, Undefined, Undefined};
        CrossThreadDataOffset workDim = Undefined;
    } dispatchMetadata;

    struct {
        ArgPointer printfSurface;
    } implicitArgs;

    struct {
        std::vector<PtrOwn<Arg>> args;
    } explicitArgs;

    struct {
        SurfaceStateHeapOffset tableOffset = Undefined;
        uint32_t numSurfaceStates = 0;
    } bindingTable;

    struct {
        DynamicStateHeapOffset tableOffset = Undefined;
        uint32_t numSamplers = 0;
        DynamicStateHeapOffset borderColor = Undefined;
    } samplerTable;

    struct Attributes {
        Attributes() { flags.packed = 0U; }

        BufferAddressingMode bufferAddressingMode = StatefulAndStateless;
        ImageAddressingMode imageAddressingMode = Stateful;

        uint32_t simdSize = 8;
        uint32_t slmInlineSize = 0;
        uint32_t numLocalIdChannels = 3;

        union {
            struct {
                bool hasPrintf : 1;
                bool hasBarriers : 1;
            };
            uint32_t packed;
        } flags;
        static_assert(sizeof(Attributes::flags) == sizeof(Attributes::flags.packed), "");
    } attributes;

    template <uint32_t VecSize, typename T>
    static void setOffsetsVec(CrossThreadDataOffset (&dst)[VecSize], const T (&src)[VecSize]) {
        for (uint32_t i = 0; i < VecSize; ++i) {
            dst[i] = src[i];
        }
    }

    template <typename T>
    static bool patchNonPointer(PtrRef<uint8_t[]> buffer, uint32_t bufferSize,
                                CrossThreadDataOffset location, const T &value) {
        if (Undefined == location) {
            return false;
        }
        assert(location < bufferSize);
        *reinterpret_cast<T *>(buffer.weakRef().offsetBytesBy(location).get()) = value;
        return true;
    }

    template <uint32_t VecSize, typename T>
    static uint32_t patchVecNonPointer(PtrRef<uint8_t[]> buffer, uint32_t bufferSize,
                                       const CrossThreadDataOffset (&location)[VecSize],
                                       const T (&value)[VecSize]) {
        uint32_t numPatched = 0;
        for (uint32_t i = 0; i < VecSize; ++i) {
            numPatched += patchNonPointer(buffer, bufferSize, location[i], value[i]) ? 1 : 0;
        }
        return numPatched;
    }

    static bool patchPointer(PtrRef<uint8_t[]> buffer, uint32_t bufferSize, const ArgPointer &arg,
                             uintptr_t value) {
        if (arg.pointerSize == 8) {
            return patchNonPointer(buffer, bufferSize, arg.stateless, static_cast<uint64_t>(value));
        } else {
            assert(arg.pointerSize == 4);
            return patchNonPointer(buffer, bufferSize, arg.stateless, static_cast<uint32_t>(value));
        }
    }
};

struct FunctionImmutableData {
    FunctionImmutableData() = default;
    ~FunctionImmutableData();

    void initialize(PtrRef<void> kernelInfoRT, MemoryManager &memoryManager, const void *deviceRT,
                    uint32_t computeUnitsUsedForSratch,
                    PtrRef<GraphicsAllocation> globalConstBuffer,
                    PtrRef<GraphicsAllocation> globalVarBuffer);

    const std::vector<PtrRef<GraphicsAllocation>> &getResidencyContainer() const {
        return residencyContainer;
    }

    uint32_t getIsaSize() const;
    PtrRef<GraphicsAllocation> getIsaGraphicsAllocation() const {
        return isaGraphicsAllocation.weakRef();
    }

    uint64_t getPrivateMemorySize() const;
    PtrRef<GraphicsAllocation> getPrivateMemoryGraphicsAllocation() const {
        return privateMemoryGraphicsAllocation.weakRef();
    }

    uint32_t getCrossThreadDataSize() const { return crossThreadDataSize; }

    PtrRef<const uint8_t[]> getCrossThreadDataTemplate() const {
        return crossThreadDataTemplate.weakRefAddConst();
    }

    uint32_t getSurfaceStateHeapSize() const;
    PtrRef<const uint8_t[]> getSurfaceStateHeapTemplate() const;

    uint32_t getDynamicStateHeapDataSize() const;
    PtrRef<const uint8_t[]> getDynamicStateHeapTemplate() const;

    const FunctionSignature &getSignature() const { return signature; }

    // TODO : Remove remaining references to kernelInfoRT (e.g. printfHandler)
    PtrRef<void> getKernelInfoRT() { return kernelInfoRT.weakRef(); }

  protected:
    PtrRef<void> kernelInfoRT = nullptr;
    PtrOwn<GraphicsAllocation> isaGraphicsAllocation = nullptr;
    PtrOwn<GraphicsAllocation> privateMemoryGraphicsAllocation = nullptr;

    uint32_t crossThreadDataSize = 0;
    PtrOwn<uint8_t[]> crossThreadDataTemplate = nullptr;

    std::vector<PtrRef<GraphicsAllocation>> residencyContainer;
    FunctionSignature signature;
};

struct Function : public _xe_function_handle_t {
    template <typename Type> struct Allocator {
        static Function *allocate(Module *module) { return new Type(module); }
    };

    static Function *create(uint32_t productFamily, Module *module, const xe_function_desc_t *desc);

    virtual ~Function() = default;

    virtual xe_result_t destroy() = 0;
    virtual xe_result_t setAttribute(xe_function_set_attribute_t attr, uint32_t value) = 0;
    virtual xe_result_t getAttribute(xe_function_get_attribute_t attr, uint32_t *pValue) = 0;
    virtual xe_result_t setArgumentValue(uint32_t argIndex, size_t argSize,
                                         const void *pArgValue) = 0;
    virtual void setGroupCount(uint32_t groupCountX, uint32_t groupCountY,
                               uint32_t groupCountZ) = 0;
    virtual xe_result_t setGroupSize(uint32_t groupSizeX, uint32_t groupSizeY,
                                     uint32_t groupSizeZ) = 0;
    virtual xe_result_t suggestGroupSize(uint32_t globalSizeX, uint32_t globalSizeY,
                                         uint32_t globalSizeZ, uint32_t *groupSizeX,
                                         uint32_t *groupSizeY, uint32_t *groupSizeZ) = 0;

    virtual PtrRef<FunctionImmutableData> getImmutableData() const = 0;
    virtual PtrOwn<Function> clone() const = 0;

    virtual const std::vector<GraphicsAllocation *> &getResidencyContainer() const = 0;

    virtual void getGroupSize(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY,
                              uint32_t &outGroupSizeZ) const = 0;

    virtual uint32_t getThreadsPerThreadGroup() const = 0;
    virtual uint32_t getThreadExecutionMask() const = 0;

    virtual PtrRef<const uint8_t[]> getCrossThreadData() const = 0;
    virtual uint32_t getCrossThreadDataSize() const = 0;

    virtual PtrRef<const uint8_t[]> getPerThreadData() const = 0;
    virtual uint32_t getPerThreadDataSizeForWholeThreadGroup() const = 0;
    virtual uint32_t getPerThreadDataSize() const = 0;
    virtual PtrRef<const uint8_t[]> getSurfaceStateHeapData() const = 0;
    virtual uint32_t getSurfaceStateHeapDataSize() const = 0;

    virtual PtrRef<const uint8_t[]> getDynamicStateHeapData() const = 0;
    virtual const size_t getDynamicStateHeapDataSize() const = 0;

    virtual PtrRef<GraphicsAllocation> getPrintfBufferAllocation() = 0;
    virtual void printPrintfOutput() = 0;

    Function() = default;
    Function(const Function &) = delete;
    Function(Function &&) = delete;
    Function &operator=(const Function &) = delete;
    Function &operator=(Function &&) = delete;

    static Function *fromHandle(xe_function_handle_t handle) {
        return static_cast<Function *>(handle);
    }

    inline xe_function_handle_t toHandle() { return this; }
};

using FunctionAllocatorFn = Function *(*)(Module *module);
extern FunctionAllocatorFn functionFactory[];

template <uint32_t productFamily, typename FunctionType> struct FunctionPopulateFactory {
    FunctionPopulateFactory() {
        functionFactory[productFamily] = FunctionType::template Allocator<FunctionType>::allocate;
    }
};

} // namespace L0
