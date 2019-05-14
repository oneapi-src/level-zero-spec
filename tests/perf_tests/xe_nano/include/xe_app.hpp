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
#ifndef _XE_APP_HPP_
#define _XE_APP_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "xe_api.h"

class XeApp {
  public:
    XeApp(std::string module_path);
    ~XeApp();

    void memoryAlloc(size_t size, void **ptr);
    void memoryFree(const void *ptr);
    void functionCreate(xe_function_handle_t *function,
                        const char *pFunctionName);
    void functionDestroy(xe_function_handle_t function);
    void commandListCreate(xe_command_list_handle_t *phCommandList);
    void commandListDestroy(xe_command_list_handle_t phCommandList);
    void commandListClose(xe_command_list_handle_t phCommandList);

    void commandQueueCreate(const uint32_t command_queue_id,
                            xe_command_queue_handle_t *command_queue);
    void commandQueueDestroy(xe_command_queue_handle_t command_queue);
    void commandQueueExecuteCommandList(uint32_t numCommandLists,
                                        xe_command_list_handle_t *
                                            command_lists);
    void commandQueueSynchronize(void);

    xe_function_handle_t function;
    xe_device_handle_t device;
    xe_module_handle_t module;
    xe_command_queue_handle_t command_queue;

  private:
    std::string module_path;
    std::vector<uint8_t> load_binary_file(const std::string &file_path);
};
#endif /* _XE_APP_HPP_*/
