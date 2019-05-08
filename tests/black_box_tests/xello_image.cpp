#include "xello_worlds.h"

#include "xe_all.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

extern bool verbose;
bool verbose = false;

void testAppendImageFunction(xe_device_handle_t &device, bool &validRet) {
    const size_t elem_size = sizeof(uint32_t);
    const size_t width = 4;
    const size_t height = 4;
    const size_t size = width * height * 4;

    xe_module_handle_t module;
    xe_function_handle_t function;
    xe_command_queue_handle_t cmdQueue;
    xe_command_list_handle_t cmdList;
    xe_thread_group_dimensions_t dispatchTraits;

    xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION_CURRENT};
    cmdQueueDesc.ordinal = 0;
    cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
    SUCCESS_OR_TERMINATE(xeCommandQueueCreate(device, &cmdQueueDesc, &cmdQueue));

    xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION_CURRENT};
    SUCCESS_OR_TERMINATE(xeCommandListCreate(device, &cmdListDesc, &cmdList));

    xe_image_desc_t srcImgDesc = {XE_IMAGE_DESC_VERSION_CURRENT,
                                  XE_IMAGE_FLAG_PROGRAM_READ,
                                  XE_IMAGE_TYPE_2D,
                                  {XE_IMAGE_FORMAT_LAYOUT_32_32_32_32, XE_IMAGE_FORMAT_TYPE_UINT,
                                   XE_IMAGE_FORMAT_SWIZZLE_R, XE_IMAGE_FORMAT_SWIZZLE_G,
                                   XE_IMAGE_FORMAT_SWIZZLE_B, XE_IMAGE_FORMAT_SWIZZLE_A},
                                  width,
                                  height,
                                  1,
                                  0,
                                  0};
    xe_image_handle_t srcImg;
    xe_image_region_t srcRegion = {0, 0, 0, size * elem_size, 0, 0};

    SUCCESS_OR_TERMINATE(
        xeImageCreate(device, const_cast<const xe_image_desc_t *>(&srcImgDesc), &srcImg));

    xe_image_desc_t dstImgDesc = {XE_IMAGE_DESC_VERSION_CURRENT,
                                  XE_IMAGE_FLAG_PROGRAM_WRITE,
                                  XE_IMAGE_TYPE_2D,
                                  {XE_IMAGE_FORMAT_LAYOUT_32_32_32_32, XE_IMAGE_FORMAT_TYPE_UINT,
                                   XE_IMAGE_FORMAT_SWIZZLE_R, XE_IMAGE_FORMAT_SWIZZLE_G,
                                   XE_IMAGE_FORMAT_SWIZZLE_B, XE_IMAGE_FORMAT_SWIZZLE_A},
                                  width,
                                  height,
                                  1,
                                  0,
                                  0};
    xe_image_handle_t dstImg;
    xe_image_region_t dstRegion = {0, 0, 0, size * elem_size, 0, 0};

    SUCCESS_OR_TERMINATE(
        xeImageCreate(device, const_cast<const xe_image_desc_t *>(&dstImgDesc), &dstImg));

    uint32_t *srcBuffer = new uint32_t[size];
    uint32_t *dstBuffer = new uint32_t[size];
    for (size_t i = 0; i < size; ++i) {
        srcBuffer[i] = static_cast<uint32_t>(i % 2 ? -1 : 0);
        dstBuffer[i] = 0xff;
    }

    uint32_t spirvSize = 0;
    auto spirvModule = readBinaryFile("image_kernel.spv", spirvSize);
    SUCCESS_OR_TERMINATE_BOOL(spirvSize != 0);

    xe_module_desc_t moduleDesc = {XE_MODULE_DESC_VERSION_CURRENT};
    moduleDesc.format = XE_MODULE_FORMAT_IL_SPIRV;
    moduleDesc.pInputModule = reinterpret_cast<const uint8_t *>(spirvModule.get());
    moduleDesc.inputSize = spirvSize;
    SUCCESS_OR_TERMINATE(xeModuleCreate(device, &moduleDesc, &module, nullptr));

    xe_function_desc_t functionDesc = {XE_FUNCTION_DESC_VERSION_CURRENT};
    functionDesc.pFunctionName = "image_copy";
    SUCCESS_OR_TERMINATE(xeFunctionCreate(module, &functionDesc, &function));

    uint32_t groupSizeX = width;
    uint32_t groupSizeY = height;
    uint32_t groupSizeZ = 1u;
    SUCCESS_OR_TERMINATE(xeFunctionSuggestGroupSize(function, width, height, 1U, &groupSizeX,
                                                    &groupSizeY, &groupSizeZ));
    if (verbose) {
        std::cout << "Group size : (" << groupSizeX << ", " << groupSizeY << ", " << groupSizeZ
                  << ")" << std::endl;
    }
    SUCCESS_OR_TERMINATE(xeFunctionSetGroupSize(function, groupSizeX, groupSizeY, groupSizeZ));

    dispatchTraits.groupCountX = width / groupSizeX;
    dispatchTraits.groupCountY = height / groupSizeY;
    dispatchTraits.groupCountZ = 1u;
    if (verbose) {
        std::cerr << "Number of groups : (" << dispatchTraits.groupCountX << ", "
                  << dispatchTraits.groupCountY << ", " << dispatchTraits.groupCountZ << ")"
                  << std::endl;
    }

    SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(function, 0, sizeof(srcImg), &srcImg));
    SUCCESS_OR_TERMINATE(xeFunctionSetArgumentValue(function, 1, sizeof(dstImg), &dstImg));

    // Copy from srcBuffer->srcImg->dstImg->dstBuffer, so at the end dstBuffer = srcBuffer
    SUCCESS_OR_TERMINATE(xeCommandListAppendImageCopyFromMemory(cmdList, srcImg, srcBuffer,
                                                                &srcRegion, nullptr, 0, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandListAppendBarrier(cmdList, nullptr, 0, nullptr));
    SUCCESS_OR_TERMINATE(
        xeCommandListAppendLaunchFunction(cmdList, function, &dispatchTraits, nullptr, 0, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandListAppendBarrier(cmdList, nullptr, 0, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandListAppendImageCopyToMemory(cmdList, dstBuffer, dstImg,
                                                              &dstRegion, nullptr, 0, nullptr));

    SUCCESS_OR_TERMINATE(xeCommandListClose(cmdList));
    SUCCESS_OR_TERMINATE(xeCommandQueueExecuteCommandLists(cmdQueue, 1, &cmdList, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandQueueSynchronize(cmdQueue, std::numeric_limits<uint32_t>::max()));

    if (verbose) {
        std::cout << "src ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << static_cast<uint32_t>(srcBuffer[i]) << " ";
        }
        std::cout << std::endl;

        std::cout << "dst ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << static_cast<uint32_t>(dstBuffer[i]) << " ";
        }
        std::cout << std::endl;
    }

    validRet = (0 == memcmp(srcBuffer, dstBuffer, size * sizeof(uint32_t)));

    delete[] srcBuffer;
    delete[] dstBuffer;
    SUCCESS_OR_TERMINATE(xeImageDestroy(srcImg));
    SUCCESS_OR_TERMINATE(xeImageDestroy(dstImg));
    SUCCESS_OR_TERMINATE(xeCommandListDestroy(cmdList));
    SUCCESS_OR_TERMINATE(xeCommandQueueDestroy(cmdQueue));
}

int main(int argc, char *argv[]) {
    xe_device_handle_t device0;
    xe_device_properties_t device0Properties = {XE_DEVICE_PROPERTIES_VERSION_CURRENT};

    verbose = isVerbose(argc, argv);

    SUCCESS_OR_TERMINATE(xeInit(XE_INIT_FLAG_NONE));
    SUCCESS_OR_TERMINATE(xeDeviceGet(0, &device0));
    SUCCESS_OR_TERMINATE(xeDeviceGetProperties(device0, &device0Properties));
    std::cout << device0Properties.name << std::endl;

    bool outputValidationSuccessful;
    testAppendImageFunction(device0, outputValidationSuccessful);

    bool aubMode = isAubMode(argc, argv);
    if (aubMode == false)
        std::cout << "\nResults validation " << (outputValidationSuccessful ? "PASSED" : "FAILED")
                  << std::endl;

    int resultOnFailure = aubMode ? 0 : 1;
    return outputValidationSuccessful ? 0 : resultOnFailure;
}
