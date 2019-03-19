#include "builtins.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include "kernels/copyBufferToBufferBytes_Gen12HPcore.hpp"

namespace L0 {

preCompiledBins::preCompiledBins(const std::string &functionName) : functionName(functionName) {
    spirvSize = size_copyBufferToBufferBytes_Gen12HPcore;
    spirvModule = new char[spirvSize]();
    memcpy(spirvModule, spirv_copyBufferToBufferBytes_Gen12HPcore, spirvSize);
}

preCompiledBins compileCopyBufferToBufferBin("copyBufferToBufferBytes");

} // namespace L0
