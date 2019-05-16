#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "../xello_worlds.h"
#include "xe_api.h"

#include <iostream>
#include <limits>
#include <fstream>
#include <memory>
#include <iomanip>

bool verbose = false;

std::ofstream noOutput;
#define vcout (verbose ? (std::cout) : noOutput)

#define N (16)
#define M (16)
#define P (16)

static float hostBufA[N * M];
static float hostBufB[M * P];
static float hostBufC[N * P];
static float hostBufCCL[N * P];
static float hostBufCXE[N * P];

/* When partial compute is enabled, work is divided among several peers. */
#define PEERS 2
#define CL_PEER 0
#define XE_PEER 1

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

void printMatrix(const size_t width, const size_t height, const float *m) {
  std::cout.setf(std::ios::fixed);
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
        std::cout << std::setw(8) << std::setprecision(2) << m[y * width + x] << " ";
    }
    std::cout << '\n';
  }
}

#define printMatrixA(mat) printMatrix(N, M, mat)
#define printMatrixB(mat) printMatrix(M, P, mat)
#define printMatrixC(mat) printMatrix(N, P, mat)

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

    vcout << "xeInit...\n";
    ret = xeInit(XE_INIT_FLAG_NONE);
    if (ret) {
        std::cout << "xeInit failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeGetDevice...\n";
    ret = xeDeviceGet(0, &xeDevice);
    if (ret) {
        std::cout << "xeGetDevice failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeDeviceGetProperties...\n";
    xe_device_properties_t xeDeviceProperties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};
    ret = xeDeviceGetProperties(xeDevice, &xeDeviceProperties);
    if (ret) {
        std::cout << "xeDeviceGetProperties failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int xeInitProgram(const char *path = "mat_mult.spv", const char *functionName = "matmat_gpu") {
    xe_result_t ret;

    uint32_t spirvSize = 0;
    auto spirvModule = readBinaryFile(path, spirvSize);
    if (!spirvSize) {
        std::cout << "spirVCompilerOutput failed\n";
        return -1;
    }

    vcout << "xeModuleCreate...\n";
    xe_module_desc_t xeModuleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
    xeModuleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
    xeModuleDesc.pInputModule = reinterpret_cast<const uint8_t *>(spirvModule.get());
    xeModuleDesc.inputSize = spirvSize;
    ret = xeModuleCreate(xeDevice, &xeModuleDesc, &xeModule, nullptr);
    if (ret) {
        std::cout << "xeModuleCreate failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeFunctionCreate (" << functionName << ")...\n";
    xe_function_desc_t xeFunctionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
    xeFunctionDesc.pFunctionName = functionName;
    ret = xeFunctionCreate(xeModule, &xeFunctionDesc, &xeFunction);
    if (ret) {
        std::cout << "xeFunctionCreate failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeCommandListCreate...\n";
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

    vcout << "xeDeviceRegisterCLProgram...\n";
    ret = xeDeviceRegisterCLProgram(xeDevice, clContext, clProgram, &xeModule);
    if (ret) {
        std::cout << "xeDeviceRegisterCLProgram failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeFunctionCreate...\n";
    xe_function_desc_t xeFunctionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
    xeFunctionDesc.pFunctionName = "matmat_gpu";
    ret = xeFunctionCreate(xeModule, &xeFunctionDesc, &xeFunction);
    if (ret) {
        std::cout << "xeFunctionCreate failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeCommandListCreate...\n";
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

    vcout << "xeSharedMemAlloc...\n";
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

    vcout << "xeDeviceRegisterCLMemory...\n";

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

    vcout << "xeDeviceRegisterCLCommandQueue...\n";
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

    vcout << "xeCommandQueueCreate...\n";
    ret = xeCommandQueueCreate(xeDevice, &cmdQueueDesc, &xeCmdQueue);
    if (ret) {
        std::cout << "xeCommandQueueCreate failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int xeMemCopyIn() {
    xe_result_t ret;

    vcout << "xeCommandListAppendMemoryCopy...\n";
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

    // Dispatch function and wait
    vcout << "xeCommandListClose...\n";
    ret = xeCommandListClose(xeCmdList);
    if (ret) {
        std::cout << "xeCommandListClose failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeCommandQueueExecuteCommandLists...\n";
    ret = xeCommandQueueExecuteCommandLists(xeCmdQueue, 1, &xeCmdList, nullptr);
    if (ret) {
        std::cout << "xeCommandQueueExecuteCommandLists failed ret " << static_cast<int>(ret)
                  << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeCommandListReset...\n";
    ret = xeCommandListReset(xeCmdList);
    if (ret) {
        std::cout << "xeCommandListReset failed ret " << static_cast<int>(ret)
                  << "\n";
	return static_cast<int>(ret);
    }

    return 0;
}

int xeCompute(const bool partial = false) {
    xe_result_t ret;

    vcout << "xeFunctionSetArgumentValue...\n";
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

    if (partial) {
	cl_int peers = PEERS;
        cl_int peer = XE_PEER;

        ret = xeFunctionSetArgumentValue(xeFunction, 6, sizeof(peers), &peers);
        if (ret) {
            std::cout << "xeFunctionSetArgumentValue failed ret " << static_cast<int>(ret) << "\n";
            return static_cast<int>(ret);
        }

        ret = xeFunctionSetArgumentValue(xeFunction, 7, sizeof(peer), &peer);
        if (ret) {
            std::cout << "xeFunctionSetArgumentValue failed ret " << static_cast<int>(ret) << "\n";
            return static_cast<int>(ret);
        }
    }

    vcout << "xeFunctionSuggestGroupSize...";
    uint32_t groupSizeX = 16;
    uint32_t groupSizeY = 16;
    uint32_t groupSizeZ = 1;
    ret = xeFunctionSuggestGroupSize(xeFunction, M, N, 1U, &groupSizeX, &groupSizeY, &groupSizeZ);
    if (ret) {
        std::cout << "xeFunctionSetGroupSize failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeFunctionSetGroupSize...";
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

    vcout << "xeCommandListAppendLaunchFunction...\n";
    ret =
        xeCommandListAppendLaunchFunction(xeCmdList, xeFunction, &xeGroupDim, nullptr, 0, nullptr);
    if (ret) {
        std::cout << "xeCommandListAppendLaunchFunction failed ret " << static_cast<int>(ret)
                  << "\n";
        return static_cast<int>(ret);
    }

    // Dispatch function and wait
    vcout << "xeCommandListClose...\n";
    ret = xeCommandListClose(xeCmdList);
    if (ret) {
        std::cout << "xeCommandListClose failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeCommandQueueExecuteCommandLists...\n";
    ret = xeCommandQueueExecuteCommandLists(xeCmdQueue, 1, &xeCmdList, nullptr);
    if (ret) {
        std::cout << "xeCommandQueueExecuteCommandLists failed ret " << static_cast<int>(ret)
                  << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeCommandQueueSynchronize...\n";
    ret = xeCommandQueueSynchronize(xeCmdQueue, std::numeric_limits<uint32_t>::max());
    if (ret) {
        std::cout << "xeCommandQueueSynchronize failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeCommandListReset...\n";
    ret = xeCommandListReset(xeCmdList);
    if (ret) {
        std::cout << "xeCommandListReset failed ret " << static_cast<int>(ret)
                  << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int xeMemCopyOut() {
    xe_result_t ret;

    vcout << "xeCommandListAppendMemoryCopy...\n";
    ret = xeCommandListAppendMemoryCopy(xeCmdList, hostBufCXE, xeMemC, sizeof(hostBufCXE), nullptr, 0,
                                        nullptr);
    if (ret) {
        std::cout << "xeCommandListAppendMemoryCopy failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeCommandListClose...\n";
    ret = xeCommandListClose(xeCmdList);
    if (ret) {
        std::cout << "xeCommandListClose failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeCommandQueueExecuteCommandLists...\n";
    ret = xeCommandQueueExecuteCommandLists(xeCmdQueue, 1, &xeCmdList, nullptr);
    if (ret) {
        std::cout << "xeCommandQueueExecuteCommandLists failed ret " << static_cast<int>(ret)
                  << "\n";
        return static_cast<int>(ret);
    }

    vcout << "xeCommandListReset...\n";
    ret = xeCommandListReset(xeCmdList);
    if (ret) {
        std::cout << "xeCommandListReset failed ret " << static_cast<int>(ret)
                  << "\n";
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

    vcout << "clGetPlatformIDs...\n";
    ret = clGetPlatformIDs(1, &clPlatform, NULL);
    if (ret) {
        std::cout << "clGetPlatformIDs failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "clGetPlatformInfo...\n";
    ret = clGetPlatformInfo(clPlatform, CL_PLATFORM_NAME, 512, str, NULL);
    if (ret) {
        std::cout << "clGetPlatformInfo failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "clPlatform name " << str << "\n";

    vcout << "clGetDeviceIDs...\n";
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

    vcout << "clDevice name " << str << "\n";

    vcout << "clCreateContext...\n";
    clContext = clCreateContext(NULL, 1, &clDevice, NULL, NULL, &ret);
    if (!clContext) {
        std::cout << "clCreateContext failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "clCreateKernel...\n";
    clQueue = clCreateCommandQueueWithProperties(clContext, clDevice, 0, &ret);
    if (!clQueue) {
        std::cout << "clCreateCommandQueue failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int clInitProgram(const char *path = "mat_mult.cl", const char *functionName = "matmat_gpu") {
    cl_int ret;

    uint32_t sourceLen = 0;
    auto source = readTextFile(path, sourceLen);
    if (!sourceLen) {
        std::cout << "unable to open cl file\n";
        return -1;
    }

    vcout << "clCreateProgramWithSource...\n";
    clProgram = clCreateProgramWithSource(clContext, 1, (const char **)&source, NULL, &ret);
    if (!clProgram) {
        std::cout << "clCreateProgramWithSource failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "clBuildProgram...\n";
    ret = clBuildProgram(clProgram, 1, &clDevice, NULL, NULL, NULL);
    if (ret) {
        std::cout << "clBuildProgram failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "clCreateKernel...\n";
    clKernel = clCreateKernel(clProgram, functionName, &ret);
    if (ret) {
        std::cout << "clCreateKernel failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int clInitBuffers() {
    cl_int ret;

    vcout << "clCreateBuffer...\n";
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

int clMemCopyIn() {
    cl_int ret;

    vcout << "clEnqueueWriteBuffer...\n";
    ret = clEnqueueWriteBuffer(clQueue, clMemA, CL_TRUE, 0, sizeof(hostBufA), hostBufA, 0, nullptr,
                               &event);
    if (ret) {
        std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "clWaitForEvents...\n";
    ret = clWaitForEvents(1, &event);
    if (ret) {
        std::cout << "clWaitForEvents failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    ret = clEnqueueWriteBuffer(clQueue, clMemB, CL_TRUE, 0, sizeof(hostBufB), hostBufB, 0, nullptr,
                               &event);
    if (ret) {
        std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "clWaitForEvents...\n";
    ret = clWaitForEvents(1, &event);
    if (ret) {
        std::cout << "clWaitForEvents failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }


    return 0;
}

int clCompute(const bool partial=false) {
    int val, ret;

    vcout << "clSetKernelArg...\n";
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

    if (partial) {
        cl_int peers = PEERS;
	cl_int peer = CL_PEER;

        ret = clSetKernelArg(clKernel, 6, sizeof(peers), &peers);
        if (ret) {
            std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
            return static_cast<int>(ret);
        }
        ret = clSetKernelArg(clKernel, 7, sizeof(peer), &peer);
        if (ret) {
            std::cout << "clSetKernelArg failed ret " << static_cast<int>(ret) << "\n";
            return static_cast<int>(ret);
        }
    }

    vcout << "clEnqueueNDRangeKernel...\n";
    size_t global_work_size[] = {N, P};
    size_t local_work_size[] = {1, 1};
    ret = clEnqueueNDRangeKernel(clQueue, clKernel, 2, NULL, global_work_size, local_work_size, 0,
                                 NULL, &event);
    if (ret) {
        std::cout << "clEnqueueNDRangeKernel failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "clWaitForEvents...\n";
    ret = clWaitForEvents(1, &event);
    if (ret) {
        std::cout << "clWaitForEvents failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    return 0;
}

int clMemCopyOut() {
    cl_int ret;

    vcout << "clEnqueueReadBuffer...\n";
    ret = clEnqueueReadBuffer(clQueue, clMemC, CL_TRUE, 0, sizeof(hostBufCCL), hostBufCCL, 0, NULL,
                              &event);
    if (ret) {
        std::cout << "clEnqueueReadBuffer failed ret " << static_cast<int>(ret) << "\n";
        return static_cast<int>(ret);
    }

    vcout << "clWaitForEvents...\n";
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

                if (verbose)
		    printMatrixC(c);

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

    if (!aubMode && verbose && !goodWithBoth) {
        std::cout << "Expected result matrix:\n";
        printMatrixC(hostBufC);

        std::cout << "CL result matirx:\n";
        printMatrixC(hostBufCCL);

        std::cout << "XE result matrix:\n";
        printMatrixC(hostBufCXE);
    }

   int resultOnFailure = aubMode ? 0 : 1;

   return goodWithBoth ? 0 : resultOnFailure;
}
