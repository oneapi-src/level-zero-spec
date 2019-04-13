#include "builtins.h"

#include "kernels/copy_buffer_to_buffer_bytes.h"

#include <fstream>
#include <sstream>

namespace L0 {

preCompiledBins::preCompiledBins(const std::string &functionName) : functionName(functionName) {
    static_assert(sizeof(spirv_copyBufferToBufferBytes) == size_copyBufferToBufferBytes, "");
    spirvSize = sizeof(spirv_copyBufferToBufferBytes);
    spirvModule = new char[spirvSize]();
    memcpy(spirvModule, spirv_copyBufferToBufferBytes, spirvSize);
}

preCompiledBins compileCopyBufferToBufferBin("copyBufferToBufferBytes");

} // namespace L0
