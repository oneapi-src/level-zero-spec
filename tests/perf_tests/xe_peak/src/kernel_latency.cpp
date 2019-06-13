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

void XePeak::xe_peak_kernel_latency(L0Context &context) {
    uint64_t num_items = get_max_work_items(context) * FETCH_PER_WI;
    uint64_t global_size = (num_items / FETCH_PER_WI);
    uint64_t total_work_items = convert_cl_to_xe_work_item_count(
        global_size, context.device_compute_property.maxGroupSizeX);

    struct XeWorkGroups workgroup_info;
    total_work_items = set_workgroups(context, total_work_items, &workgroup_info);
    float latency = 0;
    xe_result_t result = XE_RESULT_SUCCESS;

    std::vector<uint8_t> binary_file = context.load_binary_file("xe_global_bw.spv");

    context.create_module(binary_file);

    void *inputBuf;
    result = xeDeviceMemAlloc(context.device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                        (num_items * sizeof(float)), 1, &inputBuf);
    if (result) {
        throw std::runtime_error("xeDeviceMemAlloc failed: " + result);
    }
    if (verbose)
        std::cout << "inputBuf device buffer allocated\n";

    void *outputBuf;
    result = xeDeviceMemAlloc(context.device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                        (num_items * sizeof(float)), 1, &outputBuf);
    if (result) {
        throw std::runtime_error("xeDeviceMemAlloc failed: " + result);
    }
    if (verbose)
        std::cout << "outputBuf device buffer allocated\n";

    xe_function_handle_t local_offset_v1;
    setup_function(context, local_offset_v1, "global_bandwidth_v1_local_offset", inputBuf,
                   outputBuf);

    ///////////////////////////////////////////////////////////////////////////
    std::cout << "Kernel Launch Latency (uS) : ";
    latency = run_kernel(context, local_offset_v1, workgroup_info,
                         TimingMeasurement::KERNEL_LAUNCH_LATENCY, false);
    std::cout << latency << "\n";

    ///////////////////////////////////////////////////////////////////////////
    std::cout << "Kernel Latency (uS) : ";
    latency = run_kernel(context, local_offset_v1, workgroup_info,
                         TimingMeasurement::KERNEL_COMPLETE_LATENCY, false);
    std::cout << latency << "\n";

    result = xeFunctionDestroy(local_offset_v1);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "local_offset_v1 Function Destroyed\n";

    result = xeMemFree(inputBuf);
    if (result) {
        throw std::runtime_error("xeMemFree failed: " + result);
    }
    if (verbose)
        std::cout << "Input Buffer freed\n";

    result = xeMemFree(outputBuf);
    if (result) {
        throw std::runtime_error("xeMemFree failed: " + result);
    }
    if (verbose)
        std::cout << "Output Buffer freed\n";

    result = xeModuleDestroy(context.module);
    if (result) {
        throw std::runtime_error("xeModuleDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "Module destroyed\n";

    print_test_complete();
}