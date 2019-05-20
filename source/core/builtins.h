#pragma once
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstdint>

namespace L0 {
class preCompiledBins {
  public:
    preCompiledBins(const std::string &moduleName);

    ~preCompiledBins() { delete[] spirvModule; }

    uint32_t getSize() { return spirvSize; }

    char *getModuleName() { return (char *)moduleName.c_str(); }

    char *getModule() { return spirvModule; }

  private:
    std::string moduleName;
    uint32_t spirvSize;
    char *spirvModule;
};
extern preCompiledBins compileCopyBufferToBufferBin;
extern preCompiledBins compileCopyBufferToBufferDecomposedBin;
} // namespace L0
