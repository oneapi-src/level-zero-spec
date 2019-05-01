#include "xello_worlds.h"

#define ENABLE_OCLOC_WRAPPER
#include "core/source/ocloc_shared.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

extern bool verbose;
bool verbose = false;

void printHelpAndExit(int code) {
    std::cerr << "Offline compiler to spirv - supported args" << std::endl;
    std::cerr << " -h    help" << std::endl;
    std::cerr << " -i    input file name (mandatory)" << std::endl;
    std::cerr << " -o    output file name (mandatory if output file required)" << std::endl;
    std::cerr << " -l    high level language (currently : CL12 or CL20, planned additions : CLXX, CM)" << std::endl;
    std::cerr << " -x    feed compiled binary into level_zero" << std::endl;
    std::exit(code);
}

template <typename ContainerT, typename IteratorT = typename ContainerT::const_iterator>
IteratorT findArg(const std::string &shortName, bool mandatory, bool needsValue, const ContainerT &args) {
    auto it = std::find(args.begin(), args.end(), shortName);
    if (it == args.end()) {
        if (mandatory) {
            std::cerr << "Mandatory argument : " << shortName << " not found" << std::endl;
            printHelpAndExit(-2);
        }
    }

    if (needsValue && ((it + 1) == args.end())) {
        std::cerr << "Argument : " << shortName << " is missing value" << std::endl;
        printHelpAndExit(-2);
    }

    return it;
}

template <typename SizeT>
inline std::unique_ptr<char[]> readFileRaw(const std::string &name, SizeT &outSize) {
    std::ifstream file(name, std::ios_base::binary);

    size_t length;
    file.seekg(0, file.end);
    length = static_cast<size_t>(file.tellg());
    file.seekg(0, file.beg);

    auto storage = std::make_unique<char[]>(length);
    file.read(storage.get(), length);

    outSize = static_cast<SizeT>(length);
    return storage;
}

int main(int argc, char *argv[]) {
    if (isAubMode(argc, argv)) {
        return 0;
    }

    verbose = isVerbose(argc, argv);

    bool mandatory, needsValue;
    std::vector<std::string> args{argv + 1, argv + argc};
    auto argHelp = findArg("-h", mandatory = false, needsValue = false, args);
    auto argInput = findArg("-i", mandatory = true, needsValue = true, args);
    auto argOutput = findArg("-o", mandatory = false, needsValue = true, args);
    auto arghlL = findArg("-l", mandatory = true, needsValue = true, args);
    auto argX = findArg("-x", mandatory = false, needsValue = false, args);
    auto hasArg = [&args](const std::vector<std::string>::const_iterator &it) { return it != args.end(); };

    if (hasArg(argHelp)) {
        printHelpAndExit(0);
    }

    std::string inputFileName = *(argInput + 1);
    uint32_t inputSize;
    auto input = readFileRaw(inputFileName, inputSize);
    if (0 == inputSize) {
        std::cerr << "Input file not valid : " << inputFileName << std::endl;
        std::exit(1);
    }
    std::string inputString{input.get(), input.get() + inputSize};

    ocloc::Output spirVCompilerOutput{};
    auto hlL = *(arghlL + 1);
    if (hlL == "CL12") {
        spirVCompilerOutput = ocloc::OclocWrapper::compileCl12ToSpirV(inputString.data());
    } else if (hlL == "CL20") {
        spirVCompilerOutput = ocloc::OclocWrapper::compileCl20ToSpirV(inputString.data());
    } else {
        std::cerr << "Unknown high level language : " << hlL << std::endl;
        printHelpAndExit(3);
    }

    if (spirVCompilerOutput.getBuildLogSize() > 0) {
        std::cerr << "CL->spirV comilation log : " << spirVCompilerOutput.getBuildLog() << std::endl;
    } else {
        std::cerr << "Build log empty" << std::endl;
    }

    std::cerr << "Build " << (spirVCompilerOutput.success() ? "SUCCESS" : "FAIL") << std::endl;

    if (hasArg(argOutput) && spirVCompilerOutput.success()) {
        std::string outputFileName = *(argOutput + 1);
        std::cerr << "Writing " << outputFileName << std::endl;
        std::ofstream(outputFileName, std::ios::binary)
            .write(reinterpret_cast<const char *>(spirVCompilerOutput.getOutput()),
                   spirVCompilerOutput.getOutputSize());
    }

    bool success = spirVCompilerOutput.success();
    if (hasArg(argX) && spirVCompilerOutput.success()) {
        std::cerr << "Feeding to L0" << std::endl;
        SUCCESS_OR_TERMINATE(xeInit(XE_INIT_FLAG_NONE));
        xe_device_handle_t device0;
        SUCCESS_OR_TERMINATE(xeDeviceGet(0, &device0));

        xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
        xe_module_handle_t module;
        moduleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
        moduleDesc.pInputModule = reinterpret_cast<const uint8_t *>(spirVCompilerOutput.getOutput());
        moduleDesc.inputSize = spirVCompilerOutput.getOutputSize();
        auto err = xeModuleCreate(device0, &moduleDesc, &module, nullptr);
        success = (err == XE_RESULT_SUCCESS);
        std::cerr << "Level zero create module : " << (success ? "SUCCESS" : "FAIL") << std::endl;
    }

    std::cerr << "Exiting with " << (success ? "SUCCESS" : "FAIL") << std::endl;

    return success ? 0 : -1;
}
