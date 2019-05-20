#include "builtins.h"

#include "kernels/copy_buffer_to_buffer_bytes.h"
#include "kernels/copy_buffer_to_buffer_decomposed.h"

#include <fstream>
#include <sstream>
#include <cassert>

namespace L0 {

preCompiledBins::preCompiledBins(const std::string &moduleName) : moduleName(moduleName) {
    const void* bytes = nullptr;

    if (moduleName == "copyBufferToBufferBytes") {
        spirvSize = sizeof(spirv_copy_buffer_to_buffer_bytes);
        bytes = spirv_copy_buffer_to_buffer_bytes;
    } else if (moduleName == "CopyBufferToBufferDecomposed") {
        spirvSize = sizeof(spirv_copy_buffer_to_buffer_decomposed);
        bytes = spirv_copy_buffer_to_buffer_decomposed;
    }

    assert(spirvSize != 0);
    spirvModule = new char[spirvSize]();
    memcpy(spirvModule, bytes, spirvSize);
}

preCompiledBins compileCopyBufferToBufferBin("copyBufferToBufferBytes");
preCompiledBins compileCopyBufferToBufferDecomposedBin("CopyBufferToBufferDecomposed");

} // namespace L0
