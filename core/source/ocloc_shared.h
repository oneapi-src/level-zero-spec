/**************************************************************************/ /**
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
* @cond DEV
* The source code contained or described herein and all documents related to the
* source code ("Material") are owned by Intel Corporation or its suppliers or
* licensors. Title to the Material remains with Intel Corporation or its suppliers
* and licensors. The Material contains trade secrets and proprietary and confidential
* information of Intel or its suppliers and licensors. The Material is protected by
* worldwide copyright and trade secret laws and treaty provisions. No part of the
* Material may be used, copied, reproduced, modified, published, uploaded, posted
* transmitted, distributed, or disclosed in any way without Intel's prior express
* written permission.
*
* No license under any patent, copyright, trade secret or other intellectual
* property right is granted to or conferred upon you by disclosure or delivery
* of the Materials, either expressly, by implication, inducement, estoppel
* or otherwise. Any license under such intellectual property rights must be
* express and approved by Intel in writing.
* @endcond
*
* @file spirv_compiler.h
*
******************************************************************************/
#ifndef _OCLOC_SHARED_H
#define _OCLOC_SHARED_H
#if defined(__cplusplus)
#pragma once
#endif

#include "xe_common.h"

#ifdef ENABLE_OCLOC_WRAPPER
#if defined(__linux__)
#include <dlfcn.h>
#define LOAD_OCLOC_LIBRARY() dlopen("libocloc_shared.so", RTLD_LAZY | RTLD_LOCAL)
#define LOAD_OCLOC_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#elif defined(_WIN32)
#include <Windows.h>
#undef max
#undef min
#define LOAD_OCLOC_LIBRARY() LoadLibraryA("ocloc_shared.dll")
#define LOAD_OCLOC_FUNCTION_PTR(LIB, FUNC_NAME) GetProcAddress((HMODULE)LIB, FUNC_NAME)
#else
#error "Unsupported OS"
#endif

#include <vector>

#endif // ENABLE_OCLOC_WRAPPER

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum _ocloc_result_t {
    OCLOC_RESULT_SUCCESS = 0,
    OCLOC_RESULT_ERROR_OUT_OF_HOST_MEMORY,
    OCLOC_RESULT_ERROR_BUILD_FAILURE,
    OCLOC_RESULT_ERROR_MISSING_FCL_LIBRARY,
    OCLOC_RESULT_ERROR_MISSING_IGC_LIBRARY,
    OCLOC_RESULT_ERROR_INCOMPATIBLE_FCL,
    OCLOC_RESULT_ERROR_INCOMPATIBLE_IGC,
    OCLOC_RESULT_ERROR_INVALID_PARAMETERS,
    OCLOC_RESULT_ERROR_UNKNOWN = 0x7fffffff,

} cloc_result_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Comiles .cl to spirv using libcommon_clang (prerequisite)
///
/// @details
///   Remember to delete outSpirv/outBuildLog even in case of failure
///
/// @remarks
///   _Analogues_
///     - ocloc
///
/// @returns
///     - 0 - success
///     - non-zero - error
__xedllexport int __xecall compileClToSpirv(const char *src,                                             // [in] Input OCL C source
                                            unsigned int sizeLen,                                        // [in] size of OCL C source in src
                                            const char *clOptions,                                       // [in][optional] OCL C options
                                            const char *internalOptions,                                 // [in][optional] internal compiler options
                                            void *allocator,                                             // [in][optional] allocator object
                                            void *(__xecall *allocateFn)(void *alllocator, size_t size), // [in] allocator function for outSpirv and buildLogOut
                                            void **outSpirv,                                             // [out] spirV
                                            unsigned int *outSpirvLen,                                   // [out] size of spirV
                                            char **outBuildLog,                                          // [out] build log
                                            unsigned int *outBuildLogLen                                 // [out] size of build log
);

typedef __xedllexport int(__xecall *compileClToSpirvFT)(const char *, unsigned int,
                                                        const char *, const char *,
                                                        void *, void *(__xecall *)(void *, unsigned int),
                                                        void **, unsigned int *,
                                                        char **, unsigned int *);

#if defined(__cplusplus)
} // extern "C"

#ifdef ENABLE_OCLOC_WRAPPER
namespace ocloc {

struct Output {
    Output(int status,
           char *output, unsigned int outputSize,
           char *buildLog, unsigned int buildLogSize) noexcept
        : status(status), output(output), outputSize(outputSize), buildLog(buildLog), buildLogSize(buildLogSize) {
    }

    Output(const Output &) noexcept = delete;
    Output(Output &&rhs) noexcept {
        delete[] this->output;
        delete[] this->buildLog;
        this->status = rhs.status;
        this->output = rhs.output;
        this->outputSize = rhs.outputSize;
        this->buildLog = rhs.buildLog;
        this->buildLogSize = rhs.buildLogSize;
        rhs.status = -1;
        rhs.output = nullptr;
        rhs.outputSize = 0;
        rhs.buildLog = nullptr;
        rhs.buildLogSize = 0;
    }
    Output &operator=(const Output &) noexcept = delete;
    Output &operator=(Output &&rhs) noexcept {
        delete[] this->output;
        delete[] this->buildLog;
        this->status = rhs.status;
        this->output = rhs.output;
        this->outputSize = rhs.outputSize;
        this->buildLog = rhs.buildLog;
        this->buildLogSize = rhs.buildLogSize;
        rhs.status = -1;
        rhs.output = nullptr;
        rhs.outputSize = 0;
        rhs.buildLog = nullptr;
        rhs.buildLogSize = 0;
        return *this;
    }

    ~Output() noexcept {
        delete[] this->output;
        delete[] this->buildLog;
    }

    bool success() const {
        return status == 0;
    }

    int getStatus() const {
        return status;
    }

    const void *getOutput() const {
        return output;
    }

    unsigned int getOutputSize() const {
        return outputSize;
    }

    const char *getBuildLog() const {
        return buildLog;
    }

    unsigned int getBuildLogSize() const {
        return buildLogSize;
    }

    void deleteBuildLog() {
        delete[] buildLog;
        buildLog = nullptr;
        buildLogSize = 0;
    }

    void deleteOutput() {
        delete[] output;
        output = nullptr;
        outputSize = 0;
    }

  protected:
    int status = -1;
    char *output = nullptr;
    unsigned int outputSize = 0;
    char *buildLog = nullptr;
    unsigned int buildLogSize = 0;
};

struct OclocWrapper {
  public:
    static Output compileClToSpirV(const char *src, const char *clOptions, const char *internalOptions) {
        char *spirV;
        unsigned int spirVSize;
        char *buildLog;
        unsigned int buildLogSize;
        auto func = getOclocFunc<compileClToSpirvFT>("compileClToSpirv");
        int result = func(src, static_cast<unsigned int>(strlen(src)),
                          clOptions, internalOptions,
                          nullptr, &allocate,
                          reinterpret_cast<void **>(&spirV), &spirVSize, &buildLog, &buildLogSize);
        return Output{result, spirV, spirVSize, buildLog, buildLogSize};
    }

    static Output compileClToSpirV(const char *src, const char *clOptions) {
        return compileClToSpirV(src, clOptions, nullptr);
    }

    static Output compileClToSpirV(const char *src) {
        return compileClToSpirV(src, nullptr, nullptr);
    }

    static Output compileCl12ToSpirV(const char *src) {
        return compileClToSpirV(src, "-cl-std=CL1.2", nullptr);
    }

    static Output compileCl20ToSpirV(const char *src) {
        return compileClToSpirV(src, "-cl-std=CL2.0", nullptr);
    }

  protected:
    static void *__xecall allocate(void *, unsigned int size) {
        return new char[size];
    }

    template <typename T>
    static T getOclocFunc(const char *name) {
        return reinterpret_cast<T>(getOclocFuncImpl(name));
    }

    static void *getOclocFuncImpl(const char *name) {
        static auto lib = LOAD_OCLOC_LIBRARY();
        return LOAD_OCLOC_FUNCTION_PTR(lib, name);
    }
};

} // namespace ocloc

#endif // ENABLE_OCLOC_WRAPPER

#endif // __cplusplus

#ifdef ENABLE_OCLOC_WRAPPER
#undef LOAD_OCLOC_LIBRARY
#undef LOAD_OCLOC_FUNCTION_PTR
#endif

#endif // _OCLOC_SHARED_H
