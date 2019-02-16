#pragma once
#include "module.h"

#include "white_box.h"
#include "mock.h"

#include "igc.opencl.h" // temporarily to instrument NEO's compiler interface

#include <algorithm>
#include <cstdint>
#include <ostream>
#include <memory>
#include <unordered_map>
#include <utility>

// temporarily to instrument NEO's compiler interface
namespace Os {
    extern const char *frontEndDllName;
    extern const char *igcDllName;
}

namespace xe {

namespace ult {

template<>
struct Mock<Module> : public Module {
    Mock() = default;
    virtual ~Mock() = default;

    MOCK_METHOD2(createFunction, xe_result_t (const xe_function_desc_t *desc, xe_function_handle_t *phFunction));
    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_CONST_METHOD0(getDevice, Device*());
};

template<>
struct Mock<Function> : public Function {
    Mock() = default;
    virtual ~Mock() = default;

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_CONST_METHOD0(getModule, Module*());
    MOCK_CONST_METHOD0(getIsaHostMem, const void *());
    MOCK_CONST_METHOD0(getIsaSize, size_t());
    MOCK_CONST_METHOD0(getSimdSize, uint32_t());
};

template<>
struct Mock<FunctionArgs> : public FunctionArgs {
    Mock() = default;
    virtual ~Mock() = default;

    MOCK_METHOD0(destroy, xe_result_t());
    MOCK_METHOD3(setValue, xe_result_t(uint32_t argIndex, size_t argSize, const void *pArgValue));
    MOCK_CONST_METHOD0(getCrossThreadDataHostMem, const void *());
    MOCK_CONST_METHOD0(getCrossThreadDataSize, size_t());
    MOCK_CONST_METHOD0(getResidencyContainer, const std::vector<GraphicsAllocation *> &());
    MOCK_METHOD3(setGroupSize, void(uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ));
    MOCK_CONST_METHOD3(getGroupSize, void(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY, uint32_t &outGroupSizeZ));
    MOCK_CONST_METHOD0(getPerThreadDataHostMem, const void *());
    MOCK_CONST_METHOD0(getPerThreadDataSize, size_t());
};

struct SpecializedFunctionMock : Mock<Function> {
    SpecializedFunctionMock(uint32_t simdSize,
                            const void *isa, size_t isaSize, 
                            const void *crossThreadDataBase, size_t crosssThreadDataBaseSize,
                            const void *perThreadDataBase, size_t perThreadDataBaseSize,
                            uint32_t groupSizeXInPerThreadDataBase, uint32_t groupSizeYInPerThreadDataBase, uint32_t groupSizeZInPerThreadDataBase,
                            const std::pair<int, int> *bufferArgOffsetPairs, size_t numBufferArgOffsetPairs)
                            : simdSize(simdSize), isa(isa), isaSize(isaSize),
                              crossThreadDataBase(crossThreadDataBase), crosssThreadDataBaseSize(crosssThreadDataBaseSize),
                              perThreadDataBase(perThreadDataBase), perThreadDataBaseSize(perThreadDataBaseSize),
                              groupSizeXInPerThreadDataBase(groupSizeXInPerThreadDataBase), groupSizeYInPerThreadDataBase(groupSizeYInPerThreadDataBase), groupSizeZInPerThreadDataBase(groupSizeZInPerThreadDataBase){
        auto bufferArgOffsetPairsIt = bufferArgOffsetPairs;
        auto bufferArgOffsetPairsEnd = bufferArgOffsetPairsIt + numBufferArgOffsetPairs;
        while(bufferArgOffsetPairsIt < bufferArgOffsetPairsEnd){
            bufferArgOffsetMap[bufferArgOffsetPairsIt->first] = bufferArgOffsetPairsIt->second;
            ++bufferArgOffsetPairsIt;
        }
    }

    uint32_t getSimdSize() const override {
        return simdSize;
    }

    const void *getIsaHostMem() const override {
        return isa;
    }

    size_t getIsaSize() const override {
        return isaSize;
    }

    uint32_t simdSize;
    const void *isa;
    size_t isaSize;
    const void *crossThreadDataBase;
    size_t crosssThreadDataBaseSize;
    std::unordered_map<int, int> bufferArgOffsetMap;
    const void *perThreadDataBase;
    size_t perThreadDataBaseSize;
    uint32_t groupSizeXInPerThreadDataBase;
    uint32_t groupSizeYInPerThreadDataBase;
    uint32_t groupSizeZInPerThreadDataBase;
};

struct SpecializedFunctionArgsMock : Mock<FunctionArgs> {
    SpecializedFunctionArgsMock(SpecializedFunctionMock *function, const std::vector<xe::GraphicsAllocation *> &allocationsForResidency) 
        : function(function), allocationsForResidency(allocationsForResidency) { 
        auto crossThreadBaseBeg = reinterpret_cast<const uint8_t *>(function->crossThreadDataBase);
        crossThreadData.assign(crossThreadBaseBeg, crossThreadBaseBeg + function->crosssThreadDataBaseSize);
    }

    xe_result_t setValue(uint32_t argIndex, size_t argSize, const void *pArgValue) override {
        auto it = function->bufferArgOffsetMap.find(argIndex);
        if(it == function->bufferArgOffsetMap.end()){
            // not a buffer arg, just assume what's in crossthread data is good enough
            return XE_RESULT_SUCCESS;
        }
        *reinterpret_cast<uintptr_t *>(&crossThreadData[it->second]) = *reinterpret_cast<const uintptr_t*>(pArgValue);
        return XE_RESULT_SUCCESS;
    }

    const void *getCrossThreadDataHostMem() const override {
        return crossThreadData.data();
    }

    size_t getCrossThreadDataSize() const override {
        return function->crosssThreadDataBaseSize;
    }

    const std::vector<GraphicsAllocation *> &getResidencyContainer() const override {
        return allocationsForResidency;
    }

    void setGroupSize(uint32_t groupSizeX, uint32_t groupSizeY, uint32_t groupSizeZ) override {
        // assert/warning  that perThreadData is precompiled?
    }

    void getGroupSize(uint32_t &outGroupSizeX, uint32_t &outGroupSizeY, uint32_t &outGroupSizeZ) const override {
        outGroupSizeX = function->groupSizeXInPerThreadDataBase;
        outGroupSizeY = function->groupSizeYInPerThreadDataBase;
        outGroupSizeZ = function->groupSizeZInPerThreadDataBase;
    }

    const void *getPerThreadDataHostMem() const override {
        return function->perThreadDataBase;
    }

    size_t getPerThreadDataSize() const override {
        return function->perThreadDataBaseSize;
    }

    SpecializedFunctionMock *function;
    std::vector<xe::GraphicsAllocation *> allocationsForResidency;
    std::vector<uint8_t> crossThreadData;
};

struct UserRealCompilerGuard {
    UserRealCompilerGuard() {
        prevCompilerFcl = Os::frontEndDllName;
        prevCompilerIgc = Os::igcDllName;

        Os::frontEndDllName = FCL_LIBRARY_NAME;
        Os::igcDllName = IGC_LIBRARY_NAME;
    }

    UserRealCompilerGuard(const UserRealCompilerGuard &) = delete;
    UserRealCompilerGuard(UserRealCompilerGuard &&) = delete;
    UserRealCompilerGuard &operator=(const UserRealCompilerGuard &) = delete;
    UserRealCompilerGuard &operator=(UserRealCompilerGuard &&) = delete;

    ~UserRealCompilerGuard() {
        Os::frontEndDllName = prevCompilerFcl;
        Os::igcDllName = prevCompilerIgc;
    }

    const char *prevCompilerFcl = nullptr;
    const char *prevCompilerIgc = nullptr;
};

inline void writeAsCppArrayInitializer(const void *data, size_t dataSize, std::ostream &out) { // function taken from cloc
    assert((dataSize & 3) == 0);

    out << "{"
        << std::endl
        << "    ";

    uint32_t *dataUint = (uint32_t *)data;
    for (size_t i = 0; i < (dataSize + 3) / 4; i++) {
        if (i != 0) {
            out << ", ";
            if (i % 8 == 0) {
                out << std::endl
                    << "    ";
            }
        }
        if (i < dataSize / 4) {
            out << "0x" << std::hex << std::setw(8) << std::setfill('0') << dataUint[i];
        }
        else {
            uint32_t lastBytes = dataSize & 0x3;
            uint32_t lastUint = 0;
            uint8_t *pLastUint = (uint8_t *)&lastUint;
            for (uint32_t j = 0; j < lastBytes; j++) {
                pLastUint[sizeof(uint32_t) - 1 - j] = dataUint[i * 4 + j];
            }
            out << "0x" << std::hex << std::setw(8) << std::setfill('0') << lastUint;
        }
    }
    out << "};" << std::endl;
}

inline void writeMockData(const std::string sourceOrigin, std::string &mockName, 
                          std::string deviceName, xe::Function *function, xe::FunctionArgs *functionArgs, const std::vector<std::pair<int, uintptr_t>> &bufferArgsIndices,
                          std::ostream &out) {
    out << "#pragma once\n\n";
    out << "// This is a generated file\n";
    out << "// Check " << sourceOrigin << " for details\n\n";
    out << "static const uint32_t " << mockName << "_SimdSize_" << deviceName << " = " << function->getSimdSize() << ";\n\n";
    out << "static const uint32_t " << mockName << "_ISA_" << deviceName << "[] = \n";
    writeAsCppArrayInitializer(function->getIsaHostMem(), function->getIsaSize(), out);
    out << "\n\n";
    out << "static const uint32_t " << mockName << "_CrossThreadDataBase_" << deviceName << "[] = \n";
    writeAsCppArrayInitializer(functionArgs->getCrossThreadDataHostMem(), functionArgs->getCrossThreadDataSize(), out);
    out << "\n\n";
    out << "static const uint32_t " << mockName << "_PerThreadDataBase_" << deviceName << "[] = \n";
    writeAsCppArrayInitializer(functionArgs->getPerThreadDataHostMem(), functionArgs->getPerThreadDataSize(), out);
    out << "\n\n";
    

    out << "static const std::pair<int, int> " << mockName << "_BufferArgIndicesAndOffsets_" << deviceName << "[] = { ";
    const void *crossThreadData = functionArgs->getCrossThreadDataHostMem();
    const uintptr_t *ctdSearchBeg = reinterpret_cast<const uintptr_t*>(crossThreadData);
    const uintptr_t *ctdSearchEnd = ctdSearchBeg + functionArgs->getCrossThreadDataSize() / sizeof(uintptr_t);
    for(auto buffArgOffset : bufferArgsIndices){
        auto it = std::find(ctdSearchBeg, ctdSearchEnd, buffArgOffset.second);
        assert(it != ctdSearchEnd);
        assert(ctdSearchEnd == std::find(it + 1, ctdSearchEnd, buffArgOffset.second)); // make sure this not just random number
        auto byteOffset = ((it - ctdSearchBeg) * sizeof(uintptr_t));
        out << "{0x" << buffArgOffset.first << ", 0x" << byteOffset << "}, " ;
    }
    out << " };\n\n";

    uint32_t groupSizeX, groupSizeY, groupSizeZ;
    functionArgs->getGroupSize(groupSizeX, groupSizeY, groupSizeZ);
    out << "static uint32_t " << mockName << "_GroupSizeInPerThreadData_" << deviceName << "[] = { ";
    out << "0x" << groupSizeX << ", " << "0x" << groupSizeY << ", " << "0x" << groupSizeZ;
    out << " };\n\n";
}

} // namespace ult
} // namespace xe
