#include "ocloc_shared.h"

#include "xe_common.h"

#include "runtime/helpers/string.h"
#include "runtime/os_interface/os_inc_base.h"
#include "runtime/os_interface/os_library.h"

#include "cif/common/cif_main.h"
#include "cif/helpers/error.h"
#include "cif/import/library_api.h"
#include "ocl_igc_interface/code_type.h"
#include "ocl_igc_interface/fcl_ocl_device_ctx.h"
#include "ocl_igc_interface/igc_ocl_device_ctx.h"
#include "ocl_igc_interface/platform_helper.h"

inline bool store(const void *src, unsigned int len,
                  void *allocator, void *(__xecall *allocateFn)(void *alllocator, size_t size),
                  void **out, unsigned int &outLen) {
    if ((src == nullptr) || (len == 0)) {
        assert(len == 0);
        *out = nullptr;
        outLen = 0;
        return true;
    }

    *out = reinterpret_cast<char *>(allocateFn(allocator, len));
    if (*out == nullptr) {
        outLen = 0;
        return false;
    }

    outLen = len;
    memcpy_s(*out, outLen, src, len);
    return true;
}

__xedllexport int __xecall compileClToSpirv(const char *src,
                                            unsigned int sizeLen,
                                            const char *clOptions,
                                            const char *internalOptions,
                                            void *allocator,
                                            void *(__xecall *allocateFn)(void *alllocator, size_t size),
                                            void **outSpirv,
                                            unsigned int *outSpirvLen,
                                            char **outBuildLog,
                                            unsigned int *outBuildLogLen) {
    assert(src);
    assert(sizeLen);
    assert(allocateFn);
    assert(outSpirv);
    assert(outSpirvLen);
    assert(outBuildLog);
    assert(outBuildLogLen);
    *outSpirv = nullptr;
    *outSpirvLen = 0;
    *outBuildLog = nullptr;
    *outBuildLogLen = 0;
    if ((src == nullptr) || (sizeLen == 0)) {
        return OCLOC_RESULT_ERROR_INVALID_PARAMETERS;
    }

    std::unique_ptr<OCLRT::OsLibrary> fclLib = nullptr;
    CIF::RAII::UPtr_t<CIF::CIFMain> fclMain = nullptr;
    CIF::RAII::UPtr_t<IGC::FclOclDeviceCtxTagOCL> fclDeviceCtx = nullptr;

    fclLib.reset(OCLRT::OsLibrary::load(Os::frontEndDllName));
    if (fclLib == nullptr) {
        return OCLOC_RESULT_ERROR_MISSING_FCL_LIBRARY;
    }

    auto fclCreateMain = reinterpret_cast<CIF::CreateCIFMainFunc_t>(fclLib->getProcAddress(CIF::CreateCIFMainFuncName));
    if (fclCreateMain == nullptr) {
        return OCLOC_RESULT_ERROR_MISSING_FCL_LIBRARY;
    }

    fclMain = CIF::RAII::UPtr(fclCreateMain());
    if (fclMain == nullptr) {
        return OCLOC_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    if (false == fclMain->IsCompatible<IGC::FclOclDeviceCtx>()) {
        // given FCL is not compatible
        return OCLOC_RESULT_ERROR_INCOMPATIBLE_FCL;
    }

    fclDeviceCtx = fclMain->CreateInterface<IGC::FclOclDeviceCtxTagOCL>();
    if (fclDeviceCtx == nullptr) {
        return -2;
    }

    fclDeviceCtx->SetOclApiVersion(210); // don't care for L0
    IGC::CodeType::CodeType_t intermediateRepresentation = IGC::CodeType::spirV;

    auto fclSrc = CIF::Builtins::CreateConstBuffer(fclMain.get(), src, sizeLen);
    auto fclOptions = CIF::Builtins::CreateConstBuffer(fclMain.get(), clOptions, (clOptions != nullptr) ? strlen(clOptions) + 1 : 0);
    std::string internalOptionsWithExt = "-cl-ext=+all ";
    if (internalOptions != nullptr) {
        internalOptionsWithExt += internalOptions;
    }
    auto fclInternalOptions = CIF::Builtins::CreateConstBuffer(fclMain.get(), internalOptionsWithExt.c_str(), internalOptionsWithExt.length() + 1);

    auto fclTranslationCtx = fclDeviceCtx->CreateTranslationCtx(IGC::CodeType::oclC, intermediateRepresentation);

    if ((nullptr == fclSrc.get()) || (nullptr == fclOptions.get()) || (nullptr == fclInternalOptions.get()) || (nullptr == fclTranslationCtx.get())) {
        return OCLOC_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    auto fclOutput = fclTranslationCtx->Translate(fclSrc.get(), fclOptions.get(),
                                                  fclInternalOptions.get(), nullptr, 0);

    if ((fclOutput == nullptr) || (fclOutput->GetBuildLog() == nullptr) || (fclOutput->GetOutput() == nullptr)) {
        return OCLOC_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    if (false == store(fclOutput->GetOutput()->GetMemoryRaw(), static_cast<unsigned int>(fclOutput->GetOutput()->GetSizeRaw()),
                       allocator, allocateFn, outSpirv, *outSpirvLen)) {
        return OCLOC_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    if (false == store(fclOutput->GetBuildLog()->GetMemoryRaw(), static_cast<unsigned int>(fclOutput->GetBuildLog()->GetSizeRaw()),
                       allocator, allocateFn, reinterpret_cast<void **>(outBuildLog), *outBuildLogLen)) {
        return OCLOC_RESULT_ERROR_OUT_OF_HOST_MEMORY;
    }

    return fclOutput->Successful() ? OCLOC_RESULT_SUCCESS : OCLOC_RESULT_ERROR_BUILD_FAILURE;
}
