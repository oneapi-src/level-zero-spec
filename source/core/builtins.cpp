#include "builtins.h"

#include "kernels/copy_buffer_to_buffer_bytes.h"
#include "kernels/copy_buffer_to_buffer_decomposed.h"

#include <fstream>
#include <sstream>

namespace L0 {

preCompiledBins::preCompiledBins(const std::string &moduleName) : moduleName(moduleName) {
    if (moduleName == "copyBufferToBufferBytes") {
        spirvSize = sizeof(spirv_copy_buffer_to_buffer_bytes);
        spirvModule = spirv_copy_buffer_to_buffer_bytes;
    } else if (moduleName == "CopyBufferToBufferDecomposed") {
        spirvSize = sizeof(spirv_copy_buffer_to_buffer_decomposed);
        spirvModule = spirv_copy_buffer_to_buffer_decomposed;
    }
}

preCompiledBins compileCopyBufferToBufferBin("copyBufferToBufferBytes");
preCompiledBins compileCopyBufferToBufferDecomposedBin("CopyBufferToBufferDecomposed");

} // namespace L0
