#include "builtins.h"
#include <fstream>
#include <sstream>

namespace L0 {

preCompiledBins::preCompiledBins(const std::string &functionName):
    functionName(functionName)
{
    std::ifstream spirvFile("kernels/copyBuffer_Gen12HPcore.spv");

    spirvFile.seekg(0, spirvFile.end);
    spirvSize = static_cast<uint32_t>(spirvFile.tellg());
    spirvFile.seekg(0, spirvFile.beg);

    spirvModule =  new char[spirvSize]();
    std::ostringstream sstream;
    sstream << spirvFile.rdbuf();
    std::string str(sstream.str());
    memcpy(spirvModule, str.c_str(), spirvSize);
}

preCompiledBins compileCopyBufferToBufferBin("copyBufferToBufferBytes");

} // namespace L0
