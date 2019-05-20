#pragma once
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstdint>

namespace L0 {
class preCompiledBins {
  public:
    preCompiledBins(const std::string &moduleName);

    uint32_t getSize() { return spirvSize; }

    char *getModuleName() { return (char *)moduleName.c_str(); }

    const unsigned char *getModule() { return spirvModule; }

  private:
    std::string moduleName;
    uint32_t spirvSize;
    const unsigned char *spirvModule;
};
extern preCompiledBins compileCopyBufferToBufferBin;
extern preCompiledBins compileCopyBufferToBufferDecomposedBin;
} // namespace L0
