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

void XePeak::xe_peak_global_bw(L0Context &context) {
    float timed_lo, timed_go, timed, gbps;
    xe_result_t result = XE_RESULT_SUCCESS;
    uint64_t temp_global_size, max_total_work_items;
    struct XeWorkGroups workgroup_info;
    TimingMeasurement type = is_bandwidth_with_event_timer();

    std::vector<uint8_t> binary_file = context.load_binary_file("xe_global_bw.spv");

    context.create_module(binary_file);

    uint64_t maxItems = max_device_object_size(context) / sizeof(float) / 2;
    uint64_t numItems = roundToMultipleOf(
        maxItems, (context.device_compute_property.maxGroupSizeX * FETCH_PER_WI * 16),
        global_bw_max_size);

    numItems = set_workgroups(context, numItems, &workgroup_info);

    std::vector<float> arr(numItems);
    for (uint64_t i = 0; i < numItems; i++) {
        arr[i] = static_cast<float>(i);
    }

    void *inputBuf;
    result = xeDeviceMemAlloc(context.device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                        (numItems * sizeof(float)), 1, &inputBuf);
    if (result) {
        throw std::runtime_error("xeDeviceMemAlloc failed: " + result);
    }
    if (verbose)
        std::cout << "inputBuf device buffer allocated\n";

    void *outputBuf;
    result = xeDeviceMemAlloc(context.device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                        (numItems * sizeof(float)), 1, &outputBuf);
    if (result) {
        throw std::runtime_error("xeDeviceMemAlloc failed: " + result);
    }
    if (verbose)
        std::cout << "outputBuf device buffer allocated\n";

    result = xeCommandListAppendMemoryCopy(context.command_list, inputBuf, arr.data(),
                                           (arr.size() * sizeof(float)), nullptr, 0, nullptr);
    if (result) {
        throw std::runtime_error("xeCommandListAppendMemoryCopy failed: " + result);
    }
    if (verbose)
        std::cout << "Input buffer copy encoded\n";

    result = xeCommandListAppendBarrier(context.command_list, nullptr, 0, nullptr);
    if (result) {
        throw std::runtime_error("xeCommandListAppendExecutionBarrier failed: " + result);
    }
    if (verbose)
        std::cout << "Execution barrier appended\n";

    context.execute_commandlist_and_sync();

    /*Begin setup of Function*/

    xe_function_handle_t local_offset_v1;
    setup_function(context, local_offset_v1, "global_bandwidth_v1_local_offset", inputBuf,
                   outputBuf);
    xe_function_handle_t global_offset_v1;
    setup_function(context, global_offset_v1, "global_bandwidth_v1_global_offset", inputBuf,
                   outputBuf);
    xe_function_handle_t local_offset_v2;
    setup_function(context, local_offset_v2, "global_bandwidth_v2_local_offset", inputBuf,
                   outputBuf);
    xe_function_handle_t global_offset_v2;
    setup_function(context, global_offset_v2, "global_bandwidth_v2_global_offset", inputBuf,
                   outputBuf);
    xe_function_handle_t local_offset_v4;
    setup_function(context, local_offset_v4, "global_bandwidth_v4_local_offset", inputBuf,
                   outputBuf);
    xe_function_handle_t global_offset_v4;
    setup_function(context, global_offset_v4, "global_bandwidth_v4_global_offset", inputBuf,
                   outputBuf);
    xe_function_handle_t local_offset_v8;
    setup_function(context, local_offset_v8, "global_bandwidth_v8_local_offset", inputBuf,
                   outputBuf);
    xe_function_handle_t global_offset_v8;
    setup_function(context, global_offset_v8, "global_bandwidth_v8_global_offset", inputBuf,
                   outputBuf);
    xe_function_handle_t local_offset_v16;
    setup_function(context, local_offset_v16, "global_bandwidth_v16_local_offset", inputBuf,
                   outputBuf);
    xe_function_handle_t global_offset_v16;
    setup_function(context, global_offset_v16, "global_bandwidth_v16_global_offset", inputBuf,
                   outputBuf);

    std::cout << "Global memory bandwidth (GBPS)\n";

    ///////////////////////////////////////////////////////////////////////////
    // Vector width 1
    std::cout << "float   : ";

    // Run 2 kind of bandwidth kernel
    // lo -- local_size offset - subsequent fetches at local_size offset
    // go -- global_size offset
    temp_global_size = (numItems / FETCH_PER_WI);
    max_total_work_items = convert_cl_to_xe_work_item_count(
        temp_global_size, context.device_compute_property.maxGroupSizeX);

    max_total_work_items = set_workgroups(context, max_total_work_items, &workgroup_info);

    timed_lo = run_kernel(context, local_offset_v1, workgroup_info, type);
    timed_go = run_kernel(context, global_offset_v1, workgroup_info, type);
    timed = (timed_lo < timed_go) ? timed_lo : timed_go;

    gbps = ((float)numItems * sizeof(float)) / timed / 1e3f;
    std::cout << "GBPS: " << gbps << "\n";

    ///////////////////////////////////////////////////////////////////////////
    // Vector width 2
    std::cout << "float2   : ";

    temp_global_size = (numItems / 2 / FETCH_PER_WI);
    max_total_work_items = convert_cl_to_xe_work_item_count(
        temp_global_size, context.device_compute_property.maxGroupSizeX);

    max_total_work_items = set_workgroups(context, max_total_work_items, &workgroup_info);

    timed_lo = run_kernel(context, local_offset_v2, workgroup_info, type);
    timed_go = run_kernel(context, global_offset_v2, workgroup_info, type);
    timed = (timed_lo < timed_go) ? timed_lo : timed_go;

    gbps = ((float)numItems * sizeof(float)) / timed / 1e3f;
    std::cout << "GBPS: " << gbps << "\n";

    ///////////////////////////////////////////////////////////////////////////
    // Vector width 4
    std::cout << "float4   : ";

    temp_global_size = (numItems / 4 / FETCH_PER_WI);
    max_total_work_items = convert_cl_to_xe_work_item_count(
        temp_global_size, context.device_compute_property.maxGroupSizeX);

    max_total_work_items = set_workgroups(context, max_total_work_items, &workgroup_info);

    timed_lo = run_kernel(context, local_offset_v4, workgroup_info, type);
    timed_go = run_kernel(context, global_offset_v4, workgroup_info, type);
    timed = (timed_lo < timed_go) ? timed_lo : timed_go;

    gbps = ((float)numItems * sizeof(float)) / timed / 1e3f;
    std::cout << "GBPS: " << gbps << "\n";

    ///////////////////////////////////////////////////////////////////////////
    // Vector width 8
    std::cout << "float8   : ";

    temp_global_size = (numItems / 8 / FETCH_PER_WI);
    max_total_work_items = convert_cl_to_xe_work_item_count(
        temp_global_size, context.device_compute_property.maxGroupSizeX);

    max_total_work_items = set_workgroups(context, max_total_work_items, &workgroup_info);

    timed_lo = run_kernel(context, local_offset_v8, workgroup_info, type);
    timed_go = run_kernel(context, global_offset_v8, workgroup_info, type);
    timed = (timed_lo < timed_go) ? timed_lo : timed_go;

    gbps = ((float)numItems * sizeof(float)) / timed / 1e3f;
    std::cout << "GBPS: " << gbps << "\n";

    ///////////////////////////////////////////////////////////////////////////
    // Vector width 16
    std::cout << "float16   : ";
    temp_global_size = (numItems / 16 / FETCH_PER_WI);
    max_total_work_items = convert_cl_to_xe_work_item_count(
        temp_global_size, context.device_compute_property.maxGroupSizeX);

    max_total_work_items = set_workgroups(context, max_total_work_items, &workgroup_info);

    timed_lo = run_kernel(context, local_offset_v16, workgroup_info, type);
    timed_go = run_kernel(context, global_offset_v16, workgroup_info, type);
    timed = (timed_lo < timed_go) ? timed_lo : timed_go;

    gbps = ((float)numItems * sizeof(float)) / timed / 1e3f;
    std::cout << "GBPS: " << gbps << "\n";

    result = xeFunctionDestroy(local_offset_v1);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "local_offset_v1 Function Destroyed\n";

    result = xeFunctionDestroy(global_offset_v1);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "global_offset_v1 Function Destroyed\n";

    result = xeFunctionDestroy(local_offset_v2);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "local_offset_v2 Function Destroyed\n";

    result = xeFunctionDestroy(global_offset_v2);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "global_offset_v2 Function Destroyed\n";

    result = xeFunctionDestroy(local_offset_v4);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "local_offset_v4 Function Destroyed\n";

    result = xeFunctionDestroy(global_offset_v4);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "global_offset_v4 Function Destroyed\n";

    result = xeFunctionDestroy(local_offset_v8);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "local_offset_v8 Function Destroyed\n";

    result = xeFunctionDestroy(global_offset_v8);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "global_offset_v8 Function Destroyed\n";

    result = xeFunctionDestroy(local_offset_v16);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "local_offset_v16 Function Destroyed\n";

    result = xeFunctionDestroy(global_offset_v16);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "global_offset_v16 Function Destroyed\n";

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
