#pragma once
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstdint>

namespace L0 {
class preCompiledBins {
public:
    preCompiledBins(const std::string &functionName);

    ~preCompiledBins() {
        delete[] spirvModule;
    }

    uint32_t getSize() {
        return spirvSize;
    }

    char *getFunctionName() {
        return (char*)functionName.c_str();
    }

    char *getModule() {
        return spirvModule;
    }

private:
    std::string functionName;
    uint32_t    spirvSize;
    char        *spirvModule;
};
extern preCompiledBins compileCopyBufferToBufferBin;
} // namespace L0
