#include "icd_loader/icd_loader.h"

#include "xe_all.h"

#if defined(__linux__)
#include <dlfcn.h>
#define LOAD_DRIVER_LIBRARY() dlopen("liblevel_zero.so", RTLD_LAZY | RTLD_LOCAL)
#define CLOSE_LIBRARY(LIB) dlclose(LIB)
#define LOAD_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#elif defined(_WIN32)
#include <Windows.h>
#define LOAD_DRIVER_LIBRARY() LoadLibraryA("level_zero.dll")
#define CLOSE_LIBRARY(LIB) FreeLibrary(LIB)
#define LOAD_FUNCTION_PTR(LIB, FUNC_NAME) GetProcAddress((HMODULE)LIB, FUNC_NAME)
#else
#error "Unsupported OS"
#endif

#include <iostream>
#include <fstream>
#include <memory>

bool verbose = false;

template <bool TerminateOnFailure, typename ResulT>
inline void validate(ResulT result, const char *message) {
    if (result == 0) { // assumption 0 is success
        if (verbose) {
            std::cerr << " SUCCESS : " << message << std::endl;
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

void printDeviceProperties(const xe_device_properties_t &props);

int main(int argc, char *argv[]) {
    if ((argc >= 2) && ((0 == strcmp(argv[1], "-v")) || (0 == strcmp(argv[1], "--verbose")))) {
        verbose = true;
    }

    if (verbose) {
        std::cerr << "VERBOSE MODE ENABLED" << std::endl;
    }
    // 0. Load the driver
    auto driverLibrary = LOAD_DRIVER_LIBRARY();
    if (NULL == driverLibrary) {
        std::cerr << "Failed to load driver library\n";
        return 1;
    }
    xe_dispatch_table_t xeApi = {};
    load_xe(
        driverLibrary,
        [](void *library, const char *funcName) -> void * { return LOAD_FUNCTION_PTR(library, funcName); },
        &xeApi);

    SUCCESS_OR_TERMINATE(xeApi.xeDriverInit(XE_INIT_FLAG_NONE));

    uint32_t deviceCount;
    SUCCESS_OR_TERMINATE(xeApi.xeDriverGetDeviceCount(&deviceCount));

    xe_device_uuid_t *pUniqueIds = new xe_device_uuid_t[deviceCount]();
    SUCCESS_OR_TERMINATE(xeApi.xeDriverGetDeviceUniqueIds(deviceCount, pUniqueIds));

    for (uint32_t i = 0; i < deviceCount; i++) {
        xe_device_handle_t device;
        SUCCESS_OR_TERMINATE(xeApi.xeDriverGetDevice(&pUniqueIds[i], &device));

        xe_device_properties_t deviceProperties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};
        SUCCESS_OR_TERMINATE(xeApi.xeDeviceGetProperties(device, &deviceProperties));

        printDeviceProperties(deviceProperties);
    }

    return 0;
}

void printDeviceProperties(const xe_device_properties_t &props) {
    std::cout << "Device : "
              << "\n"
              << " * name : " << props.device_name << "\n"
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
              << " * numComputeCores : " << props.numComputeCores << "\n"
              << " * maxCommandQueuePriority : " << props.maxCommandQueuePriority << std::endl;
}
