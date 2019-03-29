#include "xe_all.h"

#include <exception>
#include <iostream>
#include <limits>
#include <fstream>
#include <memory>
#include <vector>

#define QTR(a) #a
#define TOSTR(b) QTR(b)

inline const std::vector<const char *> &getResourcesSearchLocations() {
    static std::vector<const char *> locations {
        "test_files/spv_modules/",
#if defined(OS_DATADIR)
    // later try install location when OS_DATADIR is defined
        TOSTR(OS_DATADIR),
#endif
    };
    return locations;
}

template <typename SizeT>
inline std::unique_ptr<char[]> readBinaryFile(const std::string &name, SizeT &outSize) {
    for (const char *base : getResourcesSearchLocations()) {
        std::string s(base);
        std::ifstream file(s + name, std::ios_base::binary);
        if (false == file.good()) {
            continue;
        }

        size_t length;
        file.seekg(0, file.end);
        length = static_cast<size_t>(file.tellg());
        file.seekg(0, file.beg);

        auto storage = std::make_unique<char[]>(length);
        file.read(storage.get(), length);

        outSize = static_cast<SizeT>(length);
        return storage;
    }
    outSize = 0;
    return nullptr;
}

extern bool verbose;

template <bool TerminateOnFailure, typename ResulT>
inline void validate(ResulT result, const char *message) {
    if (result == 0) { // assumption 0 is success
        if (verbose) {
            std::cerr << "SUCCESS : " << message << std::endl;
        }
        return;
    }

    std::cerr << (TerminateOnFailure ? "ERROR : " : "WARNING : ") << message << " : " << result << std::endl;
    if (TerminateOnFailure) {
        std::terminate();
    }
}

#define SUCCESS_OR_TERMINATE(CALL) validate<true>(CALL, #CALL)
#define SUCCESS_OR_TERMINATE_BOOL(FLAG) validate<true>(!(FLAG), #FLAG)
#define SUCCESS_OR_WARNING(CALL) validate<false>(CALL, #CALL)
#define SUCCESS_OR_WARNING_BOOL(FLAG) validate<false>(!(FLAG), #FLAG)

inline bool isParamEnabled(int argc, char *argv[], const char *shortName, const char *longName) {
    char **arg = &argv[1];
    char **argE = &argv[argc];

    for (; arg != argE; ++arg) {
        if ((0 == strcmp(*arg, shortName)) || (0 == strcmp(*arg, longName))) {
            return true;
        }
    }

    return false;
}

inline bool isVerbose(int argc, char *argv[]) {
    bool enabled = isParamEnabled(argc, argv, "-v", "--verbose");
    if (enabled == false) {
        return false;
    }

    std::cerr << "Verbose mode detected";

    return true;
}

inline bool isAubMode(int argc, char *argv[]) {
    bool enabled = isParamEnabled(argc, argv, "-a", "--aub");
    if (enabled == false) {
        return false;
    }

    std::cerr << "Aub mode detected";

    return true;
}

inline void printDeviceProperties(const xe_device_properties_t &props) {
    std::cout << "Device : "
              << "\n"
              << " * name : " << props.name << "\n"
              << " * vendorId : " << props.vendorId << "\n"
              << " * deviceId : " << props.deviceId << "\n"
              << " * subdeviceId : " << props.subdeviceId << "\n"
              << " * isSubdevice : " << (props.isSubdevice ? "TRUE" : "FALSE") << "\n"
              << " * numSubDevices : " << props.numSubDevices << "\n"
              << " * coreClockRate : " << props.coreClockRate << "\n"
              << " * memClockRate : " << props.memClockRate << "\n"
              << " * memGlobalBusWidth : " << props.memGlobalBusWidth << "\n"
              << " * totalLocalMemSize : " << props.totalLocalMemSize << "\n"
              << " * numAsyncComputeEngines : " << props.numAsyncComputeEngines << "\n"
              << " * numAsyncCopyEngines  : " << props.numAsyncCopyEngines << "\n"
              << " * maxCommandQueuePriority : " << props.maxCommandQueuePriority << std::endl;
}

template<typename T = uint8_t>
inline bool validate(const void *expected, const void *tested, size_t len) {
    bool resultsAreOk = true;
    size_t offset = 0;

    const T *expectedT = reinterpret_cast<const T *>(expected);
    const T *testedT = reinterpret_cast<const T *>(tested);
    uint32_t errorsCount = 0;
    constexpr uint32_t errorsMax = 20;
    while (offset < len) {
        if (expectedT[offset] != testedT[offset]) {
            resultsAreOk = false;
            if(verbose == false){
                break;
            }
            
            std::cerr << "Data mismatch expectedU8[" << offset << "] != testedU8[" << offset << "]   ->    "
                      << +expectedT[offset] << " != " << +testedT[offset] << std::endl;
            ++errorsCount;
            if (errorsCount >= errorsMax) {
                std::cerr << "Found " << errorsCount << " data mismatches - skipping further comparison " << std::endl;
                break;
            }
        }
        ++offset;
    }

    return resultsAreOk;
}
