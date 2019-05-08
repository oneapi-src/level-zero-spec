#pragma once
#include "graphics_allocation.h"
#include "module.h"
#include "mock_device.h"
#include "mock_function.h"

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <memory>
#include <unordered_map>
#include <utility>

namespace L0 {

namespace ult {

struct PrecompiledFunctionMockData {
    const uint32_t simdSize;
    const uint32_t *isa;
    const size_t isaSize;
    const uint32_t *crossThreadDataBase;
    const uint32_t crossThreadDataBaseSize;
    const uint32_t *perThreadDataBase;
    const uint32_t perThreadDataBaseSize;
    const uint32_t bindingTableStateCount;
    const uint32_t bindingTableOffset;
    const size_t surfaceStateHeapSize;
    uint32_t *surfaceStateHeap;
    const size_t dynamicStateHeapSize;
    const uint32_t *dynamicStateHeap;
    const uint32_t *samplerStateArray;
    const uint32_t *groupSizeInPerThreadDataBase;
    const std::pair<int, int> *bufferArgIndicesAndOffsets;
    const size_t bufferArgIndicesAndOffsetsCount;
    const bool hasBarriers;
    const uint32_t slmSize;
    const bool hasPrintfOutput;
};

struct PrecompiledFunctionMock : Mock<Function> {

    PrecompiledFunctionMock(const std::string &precompiledFunctionMockName,
                            const std::string &deviceName,
                            const std::vector<L0::GraphicsAllocation *> &allocationsForResidency);
    ~PrecompiledFunctionMock() override {}

    PrecompiledFunctionMock(const std::string &precompiledFunctionMockName,
                            const std::string &deviceName)
        : PrecompiledFunctionMock(precompiledFunctionMockName, deviceName, {}) {}

    PrecompiledFunctionMock(const PrecompiledFunctionMockData *precompiledFunctionMockData)
        : precompiledFunctionMockData(precompiledFunctionMockData) {
        auto bufferArgOffsetPairsIt = precompiledFunctionMockData->bufferArgIndicesAndOffsets;
        auto bufferArgOffsetPairsEnd =
            bufferArgOffsetPairsIt + precompiledFunctionMockData->bufferArgIndicesAndOffsetsCount;
        while (bufferArgOffsetPairsIt < bufferArgOffsetPairsEnd) {
            bufferArgOffsetMap[bufferArgOffsetPairsIt->first] = bufferArgOffsetPairsIt->second;
            ++bufferArgOffsetPairsIt;
        }

        ON_CALL(*this, setAttribute).WillByDefault(::testing::Return(XE_RESULT_ERROR_UNSUPPORTED));
        ON_CALL(*this, getAttribute).WillByDefault(::testing::Return(XE_RESULT_ERROR_UNSUPPORTED));
        ON_CALL(*this, getPerThreadData)
            .WillByDefault(
                ::testing::Return(bindPtrRef<const uint8_t[]>(reinterpret_cast<const uint8_t *>(
                    precompiledFunctionMockData->perThreadDataBase))));
        ON_CALL(*this, getPerThreadDataSizeForWholeThreadGroup)
            .WillByDefault(::testing::Return(precompiledFunctionMockData->perThreadDataBaseSize));
        ON_CALL(*this, getThreadExecutionMask).WillByDefault(::testing::Return(0xfffffffful));
        ON_CALL(*this, getCrossThreadData).WillByDefault(::testing::Invoke([this]() {
            return bindPtrRef<const uint8_t[]>(crossThreadData.data());
        }));
        ON_CALL(*this, getCrossThreadDataSize)
            .WillByDefault(::testing::Return(precompiledFunctionMockData->crossThreadDataBaseSize));
        ON_CALL(*this, getResidencyContainer)
            .WillByDefault(::testing::ReturnRef(allocationsForResidency));
        ON_CALL(*this, getSurfaceStateHeapData)
            .WillByDefault(::testing::Return(bindPtrRef<const uint8_t[]>(
                reinterpret_cast<const uint8_t *>(precompiledFunctionMockData->surfaceStateHeap))));
        ON_CALL(*this, getSurfaceStateHeapDataSize)
            .WillByDefault(::testing::Return(
                static_cast<uint32_t>(precompiledFunctionMockData->surfaceStateHeapSize)));
        ON_CALL(*this, getDynamicStateHeapData)
            .WillByDefault(::testing::Return(bindPtrRef<const uint8_t[]>(
                reinterpret_cast<const uint8_t *>(precompiledFunctionMockData->dynamicStateHeap))));
        ON_CALL(*this, getDynamicStateHeapDataSize)
            .WillByDefault(::testing::Return(precompiledFunctionMockData->dynamicStateHeapSize));
        ON_CALL(*this, getImmutableData)
            .WillByDefault(::testing::Return(
                bindPtrRef(&immutableData).weakRef<::L0::FunctionImmutableData>()));

        ON_CALL(*this, setArgumentValue)
            .WillByDefault(
                ::testing::Invoke([this](uint32_t argIndex, size_t argSize, const void *pArgValue) {
                    return this->setArgumentValueImpl(argIndex, argSize, pArgValue);
                }));
        ON_CALL(*this, getGroupSize)
            .WillByDefault(::testing::Invoke(
                [this](uint32_t &outGroupSizeX, uint32_t &outGroupSizeY, uint32_t &outGroupSizeZ) {
                    this->getGroupSizeImpl(outGroupSizeX, outGroupSizeY, outGroupSizeZ);
                }));
        ON_CALL(*this, getThreadsPerThreadGroup).WillByDefault(::testing::Invoke([this]() {
            return this->getThreadsPerThreadGroupImpl();
        }));

        immutableData.signature.attributes.flags.hasPrintf =
            precompiledFunctionMockData->hasPrintfOutput;
        const uint8_t *isaRaw = reinterpret_cast<const uint8_t *>(precompiledFunctionMockData->isa);
        isa.assign(isaRaw, isaRaw + precompiledFunctionMockData->isaSize);
        immutableData.isaGraphicsAllocation.rebind(new GraphicsAllocation(isa.data(), isa.size()));
        FunctionImp::funcImmData.rebind(&immutableData);
        immutableData.signature.samplerTable.tableOffset =
            precompiledFunctionMockData->samplerStateArray[0];
        immutableData.signature.samplerTable.numSamplers =
            precompiledFunctionMockData->samplerStateArray[1];
        immutableData.signature.samplerTable.borderColor =
            precompiledFunctionMockData->samplerStateArray[2];
        immutableData.signature.attributes.simdSize = precompiledFunctionMockData->simdSize;
        immutableData.signature.attributes.slmInlineSize = precompiledFunctionMockData->slmSize;
        immutableData.signature.attributes.flags.hasBarriers =
            precompiledFunctionMockData->hasBarriers;
        immutableData.signature.bindingTable.numSurfaceStates =
            precompiledFunctionMockData->bindingTableStateCount;
        immutableData.signature.bindingTable.tableOffset =
            precompiledFunctionMockData->bindingTableOffset;
    }

    // Note : test needs to intentionally opt-in to this
    void expectAnyMockFunctionCall() {
        const auto &_ = ::testing::_;
        EXPECT_CALL(*this, setAttribute(_, _)).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getAttribute(_, _)).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getPerThreadData()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getPerThreadDataSizeForWholeThreadGroup()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getThreadExecutionMask()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getCrossThreadData()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getCrossThreadDataSize()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getResidencyContainer()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, setArgumentValue(_, _, _)).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getGroupSize(_, _, _)).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getThreadsPerThreadGroup()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, setGroupCount(_, _, _)).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getSurfaceStateHeapData()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getSurfaceStateHeapDataSize()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getDynamicStateHeapData()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getDynamicStateHeapDataSize()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getImmutableData()).Times(::testing::AnyNumber());
    }

    xe_result_t setArgumentValueImpl(uint32_t argIndex, size_t argSize, const void *pArgValue) {
        auto it = bufferArgOffsetMap.find(argIndex);
        if (it == bufferArgOffsetMap.end()) {
            // not a buffer arg, just assume what's in crossthread data is good enough
            return XE_RESULT_SUCCESS;
        }
        *reinterpret_cast<uintptr_t *>(&crossThreadData[it->second]) =
            *reinterpret_cast<const uintptr_t *>(pArgValue);
        return XE_RESULT_SUCCESS;
    }

    void getGroupSizeImpl(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY,
                          uint32_t &outGroupSizeZ) const {
        outGroupSizeX = precompiledFunctionMockData->groupSizeInPerThreadDataBase[0];
        outGroupSizeY = precompiledFunctionMockData->groupSizeInPerThreadDataBase[1];
        outGroupSizeZ = precompiledFunctionMockData->groupSizeInPerThreadDataBase[2];
    }

    uint32_t getThreadsPerThreadGroupImpl() const {
        uint32_t lwsX, lwsY, lwsZ;
        this->getGroupSize(lwsX, lwsY, lwsZ);
        auto lws = lwsX * lwsY * lwsZ;
        auto simd = funcImmData->getSignature().attributes.simdSize;

        return (lws + simd - 1) / simd;
    }

    WhiteBox<::L0::FunctionImmutableData> immutableData;

    const PrecompiledFunctionMockData *precompiledFunctionMockData = nullptr;
    std::unordered_map<int, int> bufferArgOffsetMap;

    std::vector<L0::GraphicsAllocation *> allocationsForResidency;
    std::vector<uint8_t> crossThreadData;

    // Fake an allocation for ISA
    std::vector<uint8_t> isa;
};

struct PrecompiledFunctionMocksDataRegistry {
    static PrecompiledFunctionMocksDataRegistry &get() {
        static PrecompiledFunctionMocksDataRegistry registry;
        return registry;
    }

    const PrecompiledFunctionMockData *getDataFor(const std::string &functionName,
                                                  const std::string &deviceName) {
        auto perDeviceMapIt = data.find(deviceName);
        if (data.end() == perDeviceMapIt) {
            return nullptr;
        }
        auto functionDataIt = perDeviceMapIt->second.find(functionName);
        if (perDeviceMapIt->second.end() == functionDataIt) {
            return nullptr;
        }
        return functionDataIt->second;
    }

    void registerDataFor(const PrecompiledFunctionMockData *mockData,
                         const std::string &functionName, const std::string &deviceName) {
        data[deviceName][functionName] = mockData;
    }

  protected:
    using DeviceNameToPrecompiledDataMap =
        std::unordered_map<std::string, const PrecompiledFunctionMockData *>;
    using FunctionNameToPerDevicePrecompiledDataMap =
        std::unordered_map<std::string, const PrecompiledFunctionMockData *>;
    std::unordered_map<std::string, FunctionNameToPerDevicePrecompiledDataMap> data;
};

struct RegisterPrecompiledFunctionMocksData {
    RegisterPrecompiledFunctionMocksData(const PrecompiledFunctionMockData *data,
                                         const std::string &functionName,
                                         const std::string &deviceName) {
        PrecompiledFunctionMocksDataRegistry::get().registerDataFor(data, functionName, deviceName);
    }
};

inline PrecompiledFunctionMock::PrecompiledFunctionMock(
    const std::string &precompiledFunctionMockName, const std::string &deviceName,
    const std::vector<L0::GraphicsAllocation *> &allocationsForResidency)
    : PrecompiledFunctionMock(PrecompiledFunctionMocksDataRegistry::get().getDataFor(
          precompiledFunctionMockName, deviceName)) {
    this->allocationsForResidency = allocationsForResidency;
    auto crossThreadBaseBeg =
        reinterpret_cast<const uint8_t *>(precompiledFunctionMockData->crossThreadDataBase);
    crossThreadData.assign(crossThreadBaseBeg,
                           crossThreadBaseBeg +
                               precompiledFunctionMockData->crossThreadDataBaseSize);
}

inline void writeAsCppArrayInitializer(const void *data, size_t dataSize,
                                       std::ostream &out) { // function taken from cloc
    assert((dataSize & 3) == 0);

    out << "{" << std::endl << "    ";

    uint32_t *dataUint = (uint32_t *)data;
    for (size_t i = 0; i < (dataSize + 3) / 4; i++) {
        if (i != 0) {
            out << ", ";
            if (i % 8 == 0) {
                out << std::endl << "    ";
            }
        }
        if (i < dataSize / 4) {
            out << "0x" << std::hex << std::setw(8) << std::setfill('0') << dataUint[i];
        } else {
            uint32_t lastBytes = dataSize & 0x3;
            uint32_t lastUint = 0;
            uint8_t *pLastUint = (uint8_t *)&lastUint;
            for (uint32_t j = 0; j < lastBytes; j++) {
                pLastUint[sizeof(uint32_t) - 1 - j] = dataUint[i * 4 + j];
            }
            out << "0x" << std::hex << std::setw(8) << std::setfill('0') << lastUint;
        }
    }
    out << "\n};" << std::endl;
}

inline void writeMockData(const std::string sourceOrigin, std::string &mockName,
                          std::string deviceName, L0::Function *function,
                          const std::vector<std::pair<int, uintptr_t>> &bufferArgsIndices,
                          std::ostream &out) {
    out << "// This is a generated file\n";
    out << "// Check " << sourceOrigin << " for details\n\n";
    out << "#include \"tests/unit_tests/mock_module_precompiled.h\"\n"
           "\n"
           "namespace L0 {\n"
           "namespace ult {\n\n";

    std::string globalNameSimdSize = mockName + "_SimdSize_" + deviceName;
    std::string globalNameIsa = mockName + "_ISA_" + deviceName;
    std::string globalNameCrossThreadData = mockName + "_CrossThreadDataBase_" + deviceName;
    std::string globalNamePerThreadData = mockName + "_PerThreadDataBase_" + deviceName;
    std::string globalNameBorderColorData = mockName + "_BorderColorDataBase_" + deviceName;
    std::string globalNameBindingTableStateCount =
        mockName + "_BindingTableStateCount_" + deviceName;
    std::string globalNameBindingTableOffset = mockName + "_BindingTableOffset" + deviceName;
    std::string globalNameSurfaceStateHeapSize = mockName + "_SurfaceStateHeapSize_" + deviceName;
    std::string globalNameSurfaceStateHeap = mockName + "_SurfaceStateHeap_" + deviceName;
    std::string globalNameDynamicStateHeapSize = mockName + "_DynamicStateHeapSize_" + deviceName;
    std::string globalNameDynamicStateHeap = mockName + "_DynamicStateHeap_" + deviceName;
    std::string globalNameSamplerArrayData = mockName + "_SamplerArrayDataBase_" + deviceName;
    std::string globalNameBufferArgIndices = mockName + "_BufferArgIndicesAndOffsets_" + deviceName;
    std::string globalNameGroupSize = mockName + "_GroupSizeInPerThreadData_" + deviceName;
    std::string globalNamePrecompiledFunctionMockData = mockName + "_" + deviceName;
    std::string globalNameHasBarriers = mockName + "_HasBarriers_" + deviceName;
    std::string globalNameSlmSize = mockName + "_SlmSize_" + deviceName;
    std::string globalNameHasPrintfOutput = mockName + "_HasPrintfOutput_" + deviceName;

    auto immutableData = function->getImmutableData();
    auto &signature = immutableData->getSignature();

    out << "static const uint32_t " << globalNameSimdSize << " = " << signature.attributes.simdSize
        << ";\n\n";

    out << "static const uint32_t " << globalNameIsa << "[] = \n";
    writeAsCppArrayInitializer(immutableData->getIsaGraphicsAllocation()->getHostAddress(),
                               immutableData->getIsaSize(), out);
    out << "\n\n";
    out << "static const uint32_t " << globalNameCrossThreadData << "[] = \n";
    writeAsCppArrayInitializer(function->getCrossThreadData().get(),
                               function->getCrossThreadDataSize(), out);
    out << "\n\n";
    out << "static const uint32_t " << globalNamePerThreadData << "[] = \n";
    writeAsCppArrayInitializer(function->getPerThreadData().get(),
                               function->getPerThreadDataSizeForWholeThreadGroup(), out);
    out << "\n\n";

    out << "static const uint32_t " << globalNameBindingTableStateCount << " = 0x"
        << signature.bindingTable.numSurfaceStates << ";\n\n";
    out << "static const uint32_t " << globalNameBindingTableOffset << " = 0x"
        << signature.bindingTable.tableOffset << ";\n\n";

    auto sshSize = function->getSurfaceStateHeapDataSize();
    out << "static const size_t " << globalNameSurfaceStateHeapSize << " = 0x" << sshSize
        << ";\n\n";

    out << "static uint32_t " << globalNameSurfaceStateHeap << "[] =\n";
    writeAsCppArrayInitializer(function->getSurfaceStateHeapData().get(), sshSize, out);
    out << "\n\n";

    auto dshSize = function->getDynamicStateHeapDataSize();
    out << "static const size_t " << globalNameDynamicStateHeapSize << " = 0x" << dshSize
        << ";\n\n";

    out << "static const uint32_t " << globalNameDynamicStateHeap << "[] =\n";
    writeAsCppArrayInitializer(function->getDynamicStateHeapData().get(), dshSize, out);
    out << "\n\n";

    out << "static const uint32_t " << globalNameSamplerArrayData << "[] = {";
    out << "0x" << signature.samplerTable.tableOffset << ", 0x"
        << signature.samplerTable.numSamplers << ", 0x";
    out << signature.samplerTable.borderColor << "};\n";
    out << "\n\n";

    out << "static const bool " << globalNameHasBarriers << " = "
        << signature.attributes.flags.hasBarriers << ";\n\n";
    out << "static const uint32_t " << globalNameSlmSize << " = 0x"
        << signature.attributes.slmInlineSize << ";\n\n";
    out << "static const bool " << globalNameHasPrintfOutput << " = "
        << signature.attributes.flags.hasPrintf << ";\n\n";

    out << "static const std::pair<int, int> " << globalNameBufferArgIndices << "[] = { ";
    const void *crossThreadData = function->getCrossThreadData().get();
    const uintptr_t *ctdSearchBeg = reinterpret_cast<const uintptr_t *>(crossThreadData);
    const uintptr_t *ctdSearchEnd =
        ctdSearchBeg + function->getCrossThreadDataSize() / sizeof(uintptr_t);
    for (auto buffArgOffset : bufferArgsIndices) {
        auto it = std::find(ctdSearchBeg, ctdSearchEnd, buffArgOffset.second);
        assert(it != ctdSearchEnd);
        assert(ctdSearchEnd ==
               std::find(it + 1, ctdSearchEnd,
                         buffArgOffset.second)); // make sure this is not just random number
        auto byteOffset = ((it - ctdSearchBeg) * sizeof(uintptr_t));
        out << "{0x" << buffArgOffset.first << ", 0x" << byteOffset << "}, ";
    }
    if (bufferArgsIndices.empty()) {
        out << "{0x0, 0x0}";
    }
    out << " };\n\n";

    uint32_t groupSizeX, groupSizeY, groupSizeZ;
    function->getGroupSize(groupSizeX, groupSizeY, groupSizeZ);
    out << "static const uint32_t " << globalNameGroupSize << "[] = { ";
    out << "0x" << groupSizeX << ", "
        << "0x" << groupSizeY << ", "
        << "0x" << groupSizeZ;
    out << " };\n\n";

    out << "static const PrecompiledFunctionMockData " << globalNamePrecompiledFunctionMockData
        << " {\n"
        << globalNameSimdSize << ",\n"
        << globalNameIsa << ", sizeof(" << globalNameIsa << "),\n"
        << globalNameCrossThreadData << ", sizeof(" << globalNameCrossThreadData << "),\n"
        << globalNamePerThreadData << ", sizeof(" << globalNamePerThreadData << "),\n"
        << globalNameBindingTableStateCount << ",\n"
        << globalNameBindingTableOffset << ",\n"
        << globalNameSurfaceStateHeapSize << ",\n"
        << globalNameSurfaceStateHeap << ",\n"
        << globalNameDynamicStateHeapSize << ",\n"
        << globalNameDynamicStateHeap << ",\n"
        << globalNameSamplerArrayData << ",\n"
        << globalNameGroupSize << ",\n"
        << globalNameBufferArgIndices << ", sizeof(" << globalNameBufferArgIndices << ") / sizeof("
        << globalNameBufferArgIndices << "[0]),\n"
        << globalNameHasBarriers << ",\n"
        << globalNameSlmSize << ",\n"
        << globalNameHasPrintfOutput
        << "\n"
           "};\n\n";

    out << "RegisterPrecompiledFunctionMocksData Register_" << mockName << "_" << deviceName
        << "{ & " << globalNamePrecompiledFunctionMockData << ", \"" << mockName << "\", \""
        << deviceName << "\" }; \n";

    out << "\n"
           "} // namespace L0\n"
           "} // namespace ult\n";
}

inline std::unique_ptr<char[]> readBinaryTestFile(const std::string &name, size_t &outSize) {
    std::ifstream file(name, std::ios_base::binary);
    if (false == file.good()) {
        outSize = 0;
        return nullptr;
    }

    size_t length;
    file.seekg(0, file.end);
    length = static_cast<size_t>(file.tellg());
    file.seekg(0, file.beg);

    auto storage = std::make_unique<char[]>(length);
    file.read(storage.get(), length);

    outSize = length;
    return storage;
}

} // namespace ult
} // namespace L0
