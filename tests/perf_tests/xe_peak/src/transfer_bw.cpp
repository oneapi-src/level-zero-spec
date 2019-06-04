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

void XePeak::_transfer_bw_gpu_copy(L0Context &context, void *destination_buffer,
                                   void *source_buffer, size_t buffer_size) {
    Timer timer;
    float gbps, timed;
    xe_result_t result = XE_RESULT_SUCCESS;

    for (uint32_t i = 0; i < warmup_iterations; i++) {
        result = xeCommandListAppendMemoryCopy(context.command_list,
                                               destination_buffer,
                                               source_buffer, buffer_size,
                                               nullptr, 0, nullptr);
        if (result) {
            throw std::runtime_error("xeCommandListAppendMemoryCopy failed: "+
                                     result);
        }
    }
    context.execute_commandlist_and_sync();

    timer.start();
    for (uint32_t i = 0; i < iters; i++) {
        result = xeCommandListAppendMemoryCopy(context.command_list,
                                               destination_buffer,
                                               source_buffer, buffer_size,
                                               nullptr, 0, nullptr);
        if (result) {
            throw std::runtime_error("xeCommandListAppendMemoryCopy failed: " +
                                     result);
        }
    }

    context.execute_commandlist_and_sync();
    timed = timer.stopAndTime();
    timed /= static_cast<float>(iters);

    gbps = static_cast<float>(buffer_size) / timed / 1e3f;
    std::cout << "GBPS: " << gbps << std::endl;
}

void XePeak::_transfer_bw_host_copy(void *destination_buffer,
                                    void *source_buffer, size_t buffer_size) {
    Timer timer;
    float gbps, timed;

    for (uint32_t i = 0; i < warmup_iterations; i++) {
        memcpy(destination_buffer, source_buffer, buffer_size);
    }

    timer.start();
    for (uint32_t i = 0; i < iters; i++) {
        memcpy(destination_buffer, source_buffer, buffer_size);
    }
    timed = timer.stopAndTime();

    timed /= static_cast<float>(iters);
    gbps = static_cast<float>(buffer_size) / timed / 1e3f;
    std::cout << "GBPS: " << gbps << std::endl;
}

void XePeak::_transfer_bw_shared_memory(L0Context &context,
                                        std::vector<float> local_memory) {
    xe_result_t result = XE_RESULT_SUCCESS;
    void *shared_memory_buffer = nullptr;
    uint64_t number_of_items = local_memory.size();
    size_t local_memory_size = (number_of_items * sizeof(float));

    result = xeSharedMemAlloc(context.device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                              XE_HOST_MEM_ALLOC_FLAG_DEFAULT, local_memory_size,
                              1, &shared_memory_buffer);
    if (result) {
        throw std::runtime_error("xeSharedMemAlloc failed: " + result);
    }

    std::cout << "GPU Copy: Host to Shared Memory (WRITE)" << std::endl;
    _transfer_bw_gpu_copy(context, shared_memory_buffer, local_memory.data(),
                          local_memory_size);

    std::cout << "GPU Copy: Shared Memory to Host (READ)" << std::endl;
    _transfer_bw_gpu_copy(context, local_memory.data(), shared_memory_buffer,
                          local_memory_size);
    std::cout << "memcpy: Host to Shared Memory Copy (WRITE)" << std::endl;
    _transfer_bw_host_copy(shared_memory_buffer, local_memory.data(),
                           local_memory_size);
    std::cout << "memcpy: Shared Memory to Host Copy (READ)" << std::endl;
    _transfer_bw_host_copy(local_memory.data(), shared_memory_buffer,
                           local_memory_size);

    result = xeMemFree(shared_memory_buffer);
    if (result) {
        throw std::runtime_error("xeMemFree failed: " + result);
    }
}

void XePeak::xe_peak_transfer_bw(L0Context &context) {
    xe_result_t result = XE_RESULT_SUCCESS;
    uint64_t max_number_of_allocated_items =
        max_device_object_size(context) / sizeof(float) / 2;
    uint64_t number_of_items =
        roundToMultipleOf(max_number_of_allocated_items,
                          context.device_compute_property.maxGroupSizeX,
                          transfer_bw_max_size);

    std::vector<float> local_memory(number_of_items);
    for (uint64_t i = 0; i < number_of_items; i++) {
        local_memory[i] = static_cast<float>(i);
    }

    size_t local_memory_size = (local_memory.size() * sizeof(float));

    void *device_buffer;
    result = xeDeviceMemAlloc(context.device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                        sizeof(float) * number_of_items, 1, &device_buffer);
    if (result) {
        throw std::runtime_error("xeDeviceMemAlloc failed: " + result);
    }
    if (verbose)
        std::cout << "device buffer allocated\n";

    std::cout << "Transfer Bandwidth (GBPS)\n";

    std::cout << "GPU Copy: Host to Device (WRITE)\n";
    _transfer_bw_gpu_copy(context, device_buffer, local_memory.data(),
                          local_memory_size);

    std::cout << "GPU Copy: Device to Host (READ)\n";
    /*TODO: Add support for timing the enqueue using event timers*/
    _transfer_bw_gpu_copy(context, local_memory.data(), device_buffer,
                          local_memory_size);

    _transfer_bw_shared_memory(context, local_memory);

    result = xeMemFree(device_buffer);
    if (result) {
        throw std::runtime_error("xeMemFree failed: " + result);
    }
    if (verbose)
        std::cout << "Device Buffer freed\n";

    print_test_complete();
}
