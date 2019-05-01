#include "xello_worlds.h"

#include "xe_all.h"

#include <iostream>
#include <fstream>
#include <memory>

extern bool verbose;
bool verbose = false;

void testAppendImageCopy(xe_device_handle_t &device, bool &validRet) {

    const size_t width = 32;
    const size_t height = 32;
    const size_t size = 4 * width * height * sizeof(uint8_t);

    xe_command_queue_handle_t cmdQueue;
    xe_command_list_handle_t cmdList;

    xe_command_queue_desc_t cmdQueueDesc = {XE_COMMAND_QUEUE_DESC_VERSION_CURRENT};
    cmdQueueDesc.ordinal = 0;
    cmdQueueDesc.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
    SUCCESS_OR_TERMINATE(xeCommandQueueCreate(device, &cmdQueueDesc, &cmdQueue));

    xe_command_list_desc_t cmdListDesc = {XE_COMMAND_LIST_DESC_VERSION_CURRENT};
    SUCCESS_OR_TERMINATE(xeCommandListCreate(device, &cmdListDesc, &cmdList));

    xe_image_desc_t srcImgDesc = {
        XE_IMAGE_DESC_VERSION_CURRENT,
        XE_IMAGE_FLAG_PROGRAM_READ,
        XE_IMAGE_TYPE_2D,
        { XE_IMAGE_FORMAT_LAYOUT_8_8_8_8, XE_IMAGE_FORMAT_TYPE_UINT,
          XE_IMAGE_FORMAT_SWIZZLE_R, XE_IMAGE_FORMAT_SWIZZLE_G,
          XE_IMAGE_FORMAT_SWIZZLE_B, XE_IMAGE_FORMAT_SWIZZLE_A},
        width, height, 1, 0, 0};
    xe_image_handle_t srcImg;
    xe_image_region_t srcRegion = {0, 0, 0, size, 0, 0};

    SUCCESS_OR_TERMINATE(xeImageCreate(device,
                                             const_cast<const xe_image_desc_t *>(&srcImgDesc), &srcImg));

    xe_image_desc_t dstImgDesc = {
        XE_IMAGE_DESC_VERSION_CURRENT,
        XE_IMAGE_FLAG_PROGRAM_WRITE,
        XE_IMAGE_TYPE_2D,
        { XE_IMAGE_FORMAT_LAYOUT_8_8_8_8, XE_IMAGE_FORMAT_TYPE_UINT,
          XE_IMAGE_FORMAT_SWIZZLE_R, XE_IMAGE_FORMAT_SWIZZLE_G,
          XE_IMAGE_FORMAT_SWIZZLE_B, XE_IMAGE_FORMAT_SWIZZLE_A},
        width, height, 1, 0, 0};
    xe_image_handle_t dstImg;
    xe_image_region_t dstRegion = {0, 0, 0, size, 0, 0};

    SUCCESS_OR_TERMINATE(xeImageCreate(device,
                                             const_cast<const xe_image_desc_t *>(&dstImgDesc), &dstImg));

    char *srcBuffer = new char[size];
    char *dstBuffer = new char[size];
    for (size_t i = 0; i < size; ++i) {
        srcBuffer[i] = static_cast<char>(i + 1);
        dstBuffer[i] = 0;
    }

    // Copy from srcBuffer->srcImg->dstImg->dstBuffer, so at the end dstBuffer = srcBuffer
    SUCCESS_OR_TERMINATE(xeCommandListAppendImageCopyFromMemory(cmdList, srcImg, srcBuffer, &srcRegion, nullptr, 0, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandListAppendBarrier(cmdList, nullptr, 0, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandListAppendImageCopy(cmdList, dstImg, srcImg, nullptr, 0, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandListAppendBarrier(cmdList, nullptr, 0, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandListAppendImageCopyToMemory(cmdList, dstBuffer, dstImg, &dstRegion, nullptr, 0, nullptr));

    SUCCESS_OR_TERMINATE(xeCommandListClose(cmdList));
    SUCCESS_OR_TERMINATE(xeCommandQueueExecuteCommandLists(cmdQueue, 1, &cmdList, nullptr));
    SUCCESS_OR_TERMINATE(xeCommandQueueSynchronize(cmdQueue, std::numeric_limits<uint32_t>::max()));

    validRet = (0 == memcmp(srcBuffer, dstBuffer, size));

    delete[] srcBuffer;
    delete[] dstBuffer;
    SUCCESS_OR_TERMINATE(xeImageDestroy(dstImg));
    SUCCESS_OR_TERMINATE(xeImageDestroy(srcImg));
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
    testAppendImageCopy(device0, outputValidationSuccessful);

    bool aubMode = isAubMode(argc, argv);
    if (aubMode == false)
        std::cout << "\nResults validation " << (outputValidationSuccessful ? "PASSED" : "FAILED") << std::endl;

    int resultOnFailure = aubMode ? 0 : 1;
    return outputValidationSuccessful ? 0 : resultOnFailure;
}
