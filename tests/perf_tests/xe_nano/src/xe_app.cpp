/*
 * Copyright(c) 2019 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "xe_app.hpp"
#include "common.hpp"
bool verbose = false;

std::vector<uint8_t> XeApp::load_binary_file(const std::string
                                                 &file_path) {
    if (verbose)
        std::cout << "File path: " << file_path << std::endl;
    std::ifstream stream(file_path, std::ios::in | std::ios::binary);

    std::vector<uint8_t> binary_file;
    if (!stream.good()) {
        std::cerr << "Failed to load binary file: " << file_path;
        return binary_file;
    }

    size_t length = 0;
    stream.seekg(0, stream.end);
    length = static_cast<size_t>(stream.tellg());
    stream.seekg(0, stream.beg);
    if (verbose)
        std::cout << "Binary file length: " << length << std::endl;

    binary_file.resize(length);
    stream.read(reinterpret_cast<char *>(binary_file.data()), length);
    if (verbose)
        std::cout << "Binary file loaded" << std::endl;

    return binary_file;
}

XeApp::XeApp(std::string module_path) {
    device = nullptr;
    module = nullptr;
    function = nullptr;
    command_queue = nullptr;
    this->module_path = module_path;

    SUCCESS_OR_TERMINATE(xeInit(XE_INIT_FLAG_NONE));

    uint32_t device_count = 0;
    SUCCESS_OR_TERMINATE(xeDeviceGetCount(&device_count));

    const uint32_t default_device = 0;
    SUCCESS_OR_TERMINATE(xeDeviceGet(default_device, &device));

    const std::vector<uint8_t> binary_file = load_binary_file(module_path);
    std::cout << std::endl;

    xe_module_desc_t module_description;
    module_description.version = XE_MODULE_DESC_VERSION_CURRENT;
    module_description.format = XE_MODULE_FORMAT_IL_SPIRV;
    module_description.inputSize = binary_file.size();
    module_description.pInputModule = binary_file.data();
    module_description.pBuildFlags = nullptr;

    SUCCESS_OR_TERMINATE(xeModuleCreate(device, &module_description,
                                              &module, nullptr));
    commandQueueCreate(0, /* command_queue_id */
                       &command_queue);
}

XeApp::~XeApp(void) {
    commandQueueDestroy(command_queue);
    SUCCESS_OR_TERMINATE(xeModuleDestroy(module));
}

void XeApp::memoryAlloc(size_t size, void **ptr) {
    SUCCESS_OR_TERMINATE(
        xeDeviceMemAlloc(device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                   size, 1, ptr));
}

void XeApp::memoryFree(const void *ptr) {
    SUCCESS_OR_TERMINATE(xeMemFree(ptr));
}

void XeApp::functionCreate(xe_function_handle_t *function,
                           const char *pFunctionName) {
    xe_function_desc_t function_description;
    function_description.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    function_description.flags = XE_FUNCTION_FLAG_NONE;
    function_description.pFunctionName = pFunctionName;

    SUCCESS_OR_TERMINATE(xeFunctionCreate(module,
                                                &function_description,
                                                function));
}

void XeApp::functionDestroy(xe_function_handle_t function) {
    SUCCESS_OR_TERMINATE(xeFunctionDestroy(function));
}

void XeApp::commandListCreate(xe_command_list_handle_t *phCommandList) {
    xe_command_list_desc_t command_list_description;
    command_list_description.version = XE_COMMAND_LIST_DESC_VERSION_CURRENT;

    SUCCESS_OR_TERMINATE(xeCommandListCreate(device,
                                                   &command_list_description,
                                                   phCommandList));
}

void XeApp::commandListDestroy(xe_command_list_handle_t command_list) {
    SUCCESS_OR_TERMINATE(xeCommandListDestroy(command_list));
}

void XeApp::commandListClose(xe_command_list_handle_t command_list) {
    SUCCESS_OR_TERMINATE(xeCommandListClose(command_list));
}

void XeApp::commandQueueCreate(const uint32_t command_queue_id,
                               xe_command_queue_handle_t
                                   *command_queue) {
    xe_command_queue_desc_t command_queue_description;
    command_queue_description.version = XE_COMMAND_QUEUE_DESC_VERSION_CURRENT;
    command_queue_description.ordinal = command_queue_id;
    command_queue_description.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;

    SUCCESS_OR_TERMINATE(
        xeCommandQueueCreate(device, &command_queue_description,
                                   command_queue));
}

void XeApp::commandQueueDestroy(xe_command_queue_handle_t
                                    command_queue) {
    SUCCESS_OR_TERMINATE(xeCommandQueueDestroy(command_queue));
}

void XeApp::commandQueueExecuteCommandList(uint32_t numCommandLists,
                                           xe_command_list_handle_t *
                                               command_lists) {
    SUCCESS_OR_TERMINATE(
        xeCommandQueueExecuteCommandLists(command_queue, numCommandLists,
                                          command_lists, nullptr));
}

void XeApp::commandQueueSynchronize(void) {
    SUCCESS_OR_TERMINATE(xeCommandQueueSynchronize(command_queue, UINT32_MAX));
}
