#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "../xello_worlds.h"
#include "xe_all.h"

#include <iostream>
#include <limits>
#include <fstream>
#include <memory>

const char *source = "__kernel void matmat_gpu("
                     "       int n,"
                     "       int m,"
                     "       int p,"
                     "       global const float *a,"
                     "       global const float *b,"
                     "       global float *c"
                     "       )"
                     "{"
                     "    ulong i = get_global_id(0);"
                     "    ulong j;"
                     "    ulong k = get_global_id(1);"
                     "    float sum = 0.0f;"
                     "    for (j = 0; j < m; j++)"
                     "        sum += a[i * m + j] * b[j * p + k];"
                     "    c[i * p + k] = sum;"
                     "}";

#define N (16)
#define M (16)
#define P (16)

static float hostBufA[N * M];
static float hostBufB[M * P];
static float hostBufC[N * P];
static float hostBufCCL[N * P];
static float hostBufCXE[N * P];

static void matmat_host(int n, int m, int p, float *a, float *b, float *c) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < p; k++) {
            float sum = 0;
            for (int j = 0; j < m; j++) {
                sum += a[i * m + j] * b[j * p + k];
            }
            c[i * p + k] = sum;
        }
    }
}

extern bool verbose;
bool verbose = false;

// CL Objects
cl_platform_id clPlatform;
cl_device_id clDevice;
cl_context clContext;
cl_program clProgram;
cl_command_queue clQueue;
cl_kernel clKernel;
cl_mem clMemA, clMemB, clMemC;
cl_event event;

// XE objects
xe_device_handle_t xeDevice;
xe_command_queue_handle_t xeCmdQueue;
xe_module_handle_t xeModule;
xe_function_handle_t xeFunction;
xe_command_list_handle_t xeCmdList;
void *xeMemA;
void *xeMemB;
void *xeMemC;

int xeInit() {
    xe_result_t ret;

    std::cout << "xeInit...\n";
    ret = xeInit(XE_INIT_FLAG_NONE);
    if (ret) {
        std::cout << "xeInit failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "xeGetDevice...\n";
    ret = xeDeviceGet(0, &xeDevice);
    if (ret) {
        std::cout << "xeGetDevice failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    xe_device_properties_t xeDeviceProperties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};
    ret = xeDeviceGetProperties(xeDevice, &xeDeviceProperties);
    if (ret) {
        std::cout << "xeDeviceGetProperties failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int xeInitProgram() {
    xe_result_t ret;

    uint32_t spirvSize = 0;
    auto spirvModule = readBinaryFile("mat_mult.spv", spirvSize);
    if (!spirvSize) {
        std::cout << "spirVCompilerOutput failed\n";
        return -1;
    }

    std::cout << "xeModuleCreate...\n";
    xe_module_desc_t xeModuleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
    xeModuleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
    xeModuleDesc.pInputModule = reinterpret_cast<const uint8_t *>(spirvModule.get());
    xeModuleDesc.inputSize = spirvSize;
    ret = xeModuleCreate(xeDevice, &xeModuleDesc, &xeModule, nullptr);
    if (ret) {
        std::cout << "xeModuleCreate failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "xeFunctionCreate...\n";
    xe_function_desc_t xeFunctionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
    xeFunctionDesc.pFunctionName = "matmat_gpu";
    ret = xeFunctionCreate(xeModule, &xeFunctionDesc, &xeFunction);
    if (ret) {
        std::cout << "xeFunctionCreate failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "xeCommandListCreate...\n";
    xe_command_list_desc_t xeCmdListDesc = {XE_COMMAND_LIST_DESC_VERSION_CURRENT};
    ret = xeCommandListCreate(xeDevice, &xeCmdListDesc, &xeCmdList);
    if (ret) {
        std::cout << "xeCommandListCreate failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int xeUseCLProgram() {
    xe_result_t ret;

    std::cout << "xeDeviceRegisterCLProgram...\n";
    ret = xeDeviceRegisterCLProgram(xeDevice, clContext, clProgram, &xeModule);
    if (ret) {
        std::cout << "xeDeviceRegisterCLProgram failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "xeFunctionCreate...\n";
    xe_function_desc_t xeFunctionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
    xeFunctionDesc.pFunctionName = "matmat_gpu";
    ret = xeFunctionCreate(xeModule, &xeFunctionDesc, &xeFunction);
    if (ret) {
        std::cout << "xeFunctionCreate failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "xeCommandListCreate...\n";
    xe_command_list_desc_t xeCmdListDesc = {XE_COMMAND_LIST_DESC_VERSION_CURRENT};
    ret = xeCommandListCreate(xeDevice, &xeCmdListDesc, &xeCmdList);
    if (ret) {
        std::cout << "xeCommandListCreate failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int xeInitBuffers() {
    xe_result_t ret;

    std::cout << "xeSharedMemAlloc...\n";
    ret = xeSharedMemAlloc(xeDevice, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                           XE_HOST_MEM_ALLOC_FLAG_DEFAULT, sizeof(hostBufA), 1, &xeMemA);
    if (ret) {
        std::cout << "xeSharedMemAlloc failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = xeSharedMemAlloc(xeDevice, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                           XE_HOST_MEM_ALLOC_FLAG_DEFAULT, sizeof(hostBufB), 1, &xeMemB);
    if (ret) {
        std::cout << "xeSharedMemAlloc failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = xeSharedMemAlloc(xeDevice, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                           XE_HOST_MEM_ALLOC_FLAG_DEFAULT, sizeof(hostBufC), 1, &xeMemC);
    if (ret) {
        std::cout << "xeSharedMemAlloc failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int xeUseCLBuffers() {
    xe_result_t ret;

    std::cout << "xeDeviceRegisterCLMemory\n";

    ret = xeDeviceRegisterCLMemory(xeDevice, clContext, clMemA, &xeMemA);
    if (ret) {
        std::cout << "xeDeviceRegisterCLMemory failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = xeDeviceRegisterCLMemory(xeDevice, clContext, clMemB, &xeMemB);
    if (ret) {
        std::cout << "xeDeviceRegisterCLMemory failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = xeDeviceRegisterCLMemory(xeDevice, clContext, clMemC, &xeMemC);
    if (ret) {
        std::cout << "xeDeviceRegisterCLMemory failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int xeUseCLCmdQueue() {
    xe_result_t ret;

    std::cout << "xeDeviceRegisterCLCommandQueue...\n";
    ret = xeDeviceRegisterCLCommandQueue(xeDevice, clContext, clQueue, &xeCmdQueue);
    if (ret) {
        std::cout << "xeDeviceRegisterCLCommandQueue failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int xeInitCmdQueue() {
    xe_result_t ret;

    xe_command_queue_desc_t cmdQueueDesc = {};
    cmdQueueDesc.version = XE_COMMAND_QUEUE_DESC_VERSION_CURRENT;
    cmdQueueDesc.ordinal = 0;
    cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;

    std::cout << "xeCommandQueueCreate...\n";
    ret = xeCommandQueueCreate(xeDevice, &cmdQueueDesc, &xeCmdQueue);
    if (ret) {
        std::cout << "xeCommandQueueCreate failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int xeCompute() {
    xe_result_t ret;

    std::cout << "xeCommandListAppendMemoryCopy...\n";
    ret = xeCommandListAppendMemoryCopy(xeCmdList, xeMemA, hostBufA, sizeof(hostBufA), nullptr, 0,
                                        nullptr);
    if (ret) {
        std::cout << "xeCommandListAppendMemoryCopy failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = xeCommandListAppendMemoryCopy(xeCmdList, xeMemB, hostBufB, sizeof(hostBufB), nullptr, 0,
                                        nullptr);
    if (ret) {
        std::cout << "xeCommandListAppendMemoryCopy failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    // Wait until memory copies are ready before launching the function
    std::cout << "xeCommandListAppendBarrier...\n";
    ret = xeCommandListAppendBarrier(xeCmdList, nullptr, 0, nullptr);
    if (ret) {
        std::cout << "xeCommandListAppendBarrier failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    int val = N;
    ret = xeFunctionSetArgumentValue(xeFunction, 0, sizeof(val), &val);
    if (ret) {
        std::cout << "xeFunctionSetArgumentValue failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    val = M;
    ret = xeFunctionSetArgumentValue(xeFunction, 1, sizeof(val), &val);
    if (ret) {
        std::cout << "xeFunctionSetArgumentValue failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    val = P;
    ret = xeFunctionSetArgumentValue(xeFunction, 2, sizeof(val), &val);
    if (ret) {
        std::cout << "xeFunctionSetArgumentValue failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = xeFunctionSetArgumentValue(xeFunction, 3, sizeof(xeMemA), &xeMemA);
    if (ret) {
        std::cout << "xeFunctionSetArgumentValue failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = xeFunctionSetArgumentValue(xeFunction, 4, sizeof(xeMemB), &xeMemB);
    if (ret) {
        std::cout << "xeFunctionSetArgumentValue failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = xeFunctionSetArgumentValue(xeFunction, 5, sizeof(xeMemC), &xeMemC);
    if (ret) {
        std::cout << "xeFunctionSetArgumentValue failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    uint32_t groupSizeX = 16;
    uint32_t groupSizeY = 16;
    uint32_t groupSizeZ = 1;
    ret = xeFunctionSuggestGroupSize(xeFunction, M, N, 1U, &groupSizeX, &groupSizeY, &groupSizeZ);
    if (ret) {
        std::cout << "xeFunctionSetGroupSize failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = xeFunctionSetGroupSize(xeFunction, groupSizeX, groupSizeY, groupSizeZ);
    if (ret) {
        std::cout << "xeFunctionSetGroupSize failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    const int groupCountX = M / groupSizeX;
    const int groupCountY = N / groupSizeY;
    xe_thread_group_dimensions_t xeGroupDim;
    xeGroupDim.groupCountX = groupCountX;
    xeGroupDim.groupCountY = groupCountY;
    xeGroupDim.groupCountZ = 1;

    std::cout << "xeCommandListAppendLaunchFunction...\n";
    ret =
        xeCommandListAppendLaunchFunction(xeCmdList, xeFunction, &xeGroupDim, nullptr, 0, nullptr);
    if (ret) {
        std::cout << "xeCommandListAppendLaunchFunction failed ret " << static_cast<int>(ret)
                  << "\n";
        return static_cast<int>(ret);
    }

    // Wait until function has completed
    std::cout << "xeCommandListAppendBarrier...\n";
    ret = xeCommandListAppendBarrier(xeCmdList, nullptr, 0, nullptr);
    if (ret) {
        std::cout << "xeCommandListAppendBarrier failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    // Copy results back
    std::cout << "xeCommandListAppendMemoryCopy...\n";
    ret = xeCommandListAppendMemoryCopy(xeCmdList, hostBufCXE, xeMemC, sizeof(hostBufB), nullptr, 0,
                                        nullptr);
    if (ret) {
        std::cout << "xeCommandListAppendMemoryCopy failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    // Dispatch function and wait
    std::cout << "xeCommandListClose...\n";
    ret = xeCommandListClose(xeCmdList);
    if (ret) {
        std::cout << "xeCommandListClose failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "xeCommandQueueExecuteCommandLists...\n";
    ret = xeCommandQueueExecuteCommandLists(xeCmdQueue, 1, &xeCmdList, nullptr);
    if (ret) {
        std::cout << "xeCommandQueueExecuteCommandLists failed ret " << static_cast<int>(ret)
                  << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "xeCommandQueueSynchronize...\n";
    ret = xeCommandQueueSynchronize(xeCmdQueue, std::numeric_limits<uint32_t>::max());
    if (ret) {
        std::cout << "xeCommandQueueSynchronize failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

void xeCleanup() {
    xeMemFree(xeMemA);
    xeMemFree(xeMemB);
    xeMemFree(xeMemC);
    xeCommandListDestroy(xeCmdList);
    xeCommandQueueDestroy(xeCmdQueue);
    xeFunctionDestroy(xeFunction);
    xeModuleDestroy(xeModule);
}

int clInit() {
    cl_int ret;
    char str[512];

    std::cout << "clGetPlatformIDs...\n";
    ret = clGetPlatformIDs(1, &clPlatform, NULL);
    if (ret) {
        std::cout << "clGetPlatformIDs failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = clGetPlatformInfo(clPlatform, CL_PLATFORM_NAME, 512, str, NULL);
    if (ret) {
        std::cout << "clGetPlatformInfo failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "clPlatform name " << str << "\n";

    std::cout << "clGetDeviceIDs...\n";
    ret = clGetDeviceIDs(clPlatform, CL_DEVICE_TYPE_ALL, 1, &clDevice, NULL);
    if (ret) {
        std::cout << "clGetPlatformInfo failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = clGetDeviceInfo(clDevice, CL_DEVICE_NAME, 512, str, NULL);
    if (ret) {
        std::cout << "clGetPlatformInfo failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "clDevice name " << str << "\n";

    std::cout << "clCreateContext...\n";
    clContext = clCreateContext(NULL, 1, &clDevice, NULL, NULL, &ret);
    if (!clContext) {
        std::cout << "clCreateContext failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "clCreateKernel...\n";
    clQueue = clCreateCommandQueueWithProperties(clContext, clDevice, 0, &ret);
    if (!clQueue) {
        std::cout << "clCreateCommandQueue failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int clInitProgram() {
    cl_int ret;

    std::cout << "clCreateProgramWithSource...\n";
    clProgram = clCreateProgramWithSource(clContext, 1, (const char **)&source, NULL, &ret);
    if (!clProgram) {
        std::cout << "clCreateProgramWithSource failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "clBuildProgram...\n";
    ret = clBuildProgram(clProgram, 1, &clDevice, NULL, NULL, NULL);
    if (ret) {
        std::cout << "clBuildProgram failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "clCreateKernel...\n";
    clKernel = clCreateKernel(clProgram, "matmat_gpu", &ret);
    if (ret) {
        std::cout << "clCreateKernel failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int clInitBuffers() {
    cl_int ret;

    std::cout << "clCreateBuffer...\n";
    clMemA = clCreateBuffer(clContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(hostBufA),
                            hostBufA, &ret);
    if (!clMemA) {
        std::cout << "clCreateBuffer failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    clMemB = clCreateBuffer(clContext, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(hostBufB),
                            hostBufB, &ret);
    if (!clMemB) {
        std::cout << "clCreateBuffer failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    clMemC = clCreateBuffer(clContext, CL_MEM_WRITE_ONLY, sizeof(hostBufC), NULL, &ret);
    if (!clMemC) {
        std::cout << "clCreateBuffer failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int clCompute() {
    int val, ret;

    std::cout << "clEnqueueWriteBuffer...\n";
    ret = clEnqueueWriteBuffer(clQueue, clMemA, CL_TRUE, 0, sizeof(hostBufA), hostBufA, 0, nullptr,
                               nullptr);
    if (ret) {
        std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = clEnqueueWriteBuffer(clQueue, clMemB, CL_TRUE, 0, sizeof(hostBufB), hostBufB, 0, nullptr,
                               nullptr);
    if (ret) {
        std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    val = N;
    ret = clSetKernelArg(clKernel, 0, sizeof(val), &val);
    if (ret) {
        std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    val = M;
    ret = clSetKernelArg(clKernel, 1, sizeof(val), &val);
    if (ret) {
        std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    val = P;
    ret = clSetKernelArg(clKernel, 2, sizeof(val), &val);
    if (ret) {
        std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = clSetKernelArg(clKernel, 3, sizeof(clMemA), &clMemA);
    if (ret) {
        std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = clSetKernelArg(clKernel, 4, sizeof(clMemB), &clMemB);
    if (ret) {
        std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = clSetKernelArg(clKernel, 5, sizeof(clMemC), &clMemC);
    if (ret) {
        std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "clEnqueueNDRangeKernel...\n";
    size_t global_work_size[] = {N, P};
    size_t local_work_size[] = {1, 1};
    ret = clEnqueueNDRangeKernel(clQueue, clKernel, 2, NULL, global_work_size, local_work_size, 0,
                                 NULL, &event);
    if (ret) {
        std::cout << "clEnqueueNDRangeKernel failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "clWaitForEvents...\n";
    ret = clWaitForEvents(1, &event);
    if (ret) {
        std::cout << "clWaitForEvents failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "clEnqueueReadBuffer...\n";
    ret = clEnqueueReadBuffer(clQueue, clMemC, CL_TRUE, 0, sizeof(hostBufCCL), hostBufCCL, 0, NULL,
                              &event);
    if (ret) {
        std::cout << "clEnqueueReadBuffer failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    std::cout << "clWaitForEvents...\n";
    ret = clWaitForEvents(1, &event);
    if (ret) {
        std::cout << "clWaitForEvents failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

void clCleanup() {
    clReleaseMemObject(clMemA);
    clReleaseMemObject(clMemB);
    clReleaseMemObject(clMemC);
    clReleaseProgram(clProgram);
    clReleaseCommandQueue(clQueue);
    clReleaseContext(clContext);
    clReleaseDevice(clDevice);
}

void initArrays() {
    float temp = 0.0f;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            hostBufA[i * M + j] = temp;
            temp += 1.0f;
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            hostBufB[i * P + j] = temp;
            temp += 1.0f;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            hostBufCCL[i * P + j] = NAN;
            hostBufCXE[i * P + j] = NAN;
            hostBufC[i * P + j] = NAN;
        }
    }

    matmat_host(N, M, P, hostBufA, hostBufB, hostBufC);
}

int validateArrays(float *c) {
    int res = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            if (c[i * P + j] != hostBufC[i * P + j]) {
                res = -1;
                std::cout << "elem[" << i << "][" << j << "] wrong: "
                          << "gpu val " << c[i * P + j] << " != "
                          << "cpu val " << hostBufC[i * P + j] << "\n";
                return -1;
            }
        }
    }
    return res;
}

int validateResults(bool aubMode) {
    bool goodWithCL = (validateArrays(hostBufCCL) == 0);
    bool goodWithXE = (validateArrays(hostBufCXE) == 0);
    bool goodWithBoth = goodWithCL && goodWithXE;

    if (aubMode == false) {
        if (goodWithCL)
            std::cout << "GOOD with CL\n";
        else
            std::cout << "ERROR with CL\n";

        if (goodWithXE)
            std::cout << "GOOD with XE\n";
        else
            std::cout << "ERROR with XE\n";
    }

    int resultOnFailure = aubMode ? 0 : 1;
    return goodWithBoth ? 0 : resultOnFailure;
}
