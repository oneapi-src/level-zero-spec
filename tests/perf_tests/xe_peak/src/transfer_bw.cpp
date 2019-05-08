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
#include "../include/xe_peak.h"

void XePeak::xe_peak_transfer_bw(L0Context &context) {
    float gbps, timed;
    xe_result_t result = XE_RESULT_SUCCESS;
    Timer timer;

    uint64_t max_number_of_allocated_items = MAX_DEVICE_OBJECT_SIZE / sizeof(float) / 2;
    uint64_t number_of_items =
        roundToMultipleOf(max_number_of_allocated_items,
                          context.device_compute_property.maxGroupSizeX, transfer_bw_max_size);

    std::vector<float> local_memory(number_of_items);
    for (uint64_t i = 0; i < number_of_items; i++) {
        local_memory[i] = static_cast<float>(i);
    }

    size_t size_of_data = (local_memory.size() * sizeof(float));

    void *device_buffer;
    result = xeMemAlloc(context.device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                        sizeof(float) * number_of_items, 1, &device_buffer);
    if (result) {
        throw std::runtime_error("xeMemAlloc failed: " + result);
    }
    if (verbose)
        std::cout << "device buffer allocated\n";

    std::cout << "Transfer Bandwidth (GBPS)\n";

    ///////////////////////////////////////////////////////////////////////////
    std::cout << "Enqueue Host to Device Copy (WRITE)\n";

    /*TODO: Add support for timing the enqueue using event timers*/
    timed = 0;

    for (uint32_t i = 0; i < warmup_iterations; i++) {
        result =
            xeCommandListAppendMemoryCopy(context.command_list, device_buffer, local_memory.data(),
                                          size_of_data, nullptr, 0, nullptr);
        if (result) {
            throw std::runtime_error("xeCommandListAppendMemoryCopy failed: " + result);
        }
    }
    context.execute_commandlist_and_sync();

    timer.start();
    for (uint32_t i = 0; i < iters; i++) {
        result =
            xeCommandListAppendMemoryCopy(context.command_list, device_buffer, local_memory.data(),
                                          size_of_data, nullptr, 0, nullptr);
        if (result) {
            throw std::runtime_error("xeCommandListAppendMemoryCopy failed: " + result);
        }
    }
    context.execute_commandlist_and_sync();
    timed = timer.stopAndTime();
    timed /= static_cast<float>(iters);

    gbps = ((float)number_of_items * sizeof(float)) / timed / 1e3f;
    std::cout << "GBPS: " << gbps << "\n";

    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    std::cout << "Enqueue Device to Host Copy (READ)\n";

    /*TODO: Add support for timing the enqueue using event timers*/
    timed = 0;

    for (uint32_t i = 0; i < warmup_iterations; i++) {
        result = xeCommandListAppendMemoryCopy(context.command_list, local_memory.data(),
                                               device_buffer, size_of_data, nullptr, 0, nullptr);
        if (result) {
            throw std::runtime_error("xeCommandListAppendMemoryCopy failed: " + result);
        }
    }
    context.execute_commandlist_and_sync();

    timer.start();
    for (uint32_t i = 0; i < iters; i++) {
        result = xeCommandListAppendMemoryCopy(context.command_list, local_memory.data(),
                                               device_buffer, size_of_data, nullptr, 0, nullptr);
        if (result) {
            throw std::runtime_error("xeCommandListAppendMemoryCopy failed: " + result);
        }
    }
    context.execute_commandlist_and_sync();
    timed = timer.stopAndTime();
    timed /= static_cast<float>(iters);

    gbps = ((float)number_of_items * sizeof(float)) / timed / 1e3f;
    std::cout << "GBPS: " << gbps << "\n";

    ///////////////////////////////////////////////////////////////////////////

    result = xeMemFree(device_buffer);
    if (result) {
        throw std::runtime_error("xeMemFree failed: " + result);
    }
    if (verbose)
        std::cout << "Device Buffer freed\n";

    print_test_complete();
}