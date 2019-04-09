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

void XePeak::peak_global_bw_setup_function(L0Context &context,
                                           xe_function_handle_t &function,
                                           const char *name, void *input, void *output) {
    xe_function_desc_t function_description;
    xe_result_t result = XE_RESULT_SUCCESS;

    function_description.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    function_description.flags = XE_FUNCTION_FLAG_NONE;
    function_description.pFunctionName = name;

    result =
        xeModuleCreateFunction(context.module, &function_description, &function);
    if (result) {
        throw std::runtime_error("xeModuleCreateFunction failed: " + result);
    }
    if (verbose)
        std::cout << "Function created\n";

    result = xeFunctionSetArgumentValue(function, 0, sizeof(input), &input);
    if (result) {
        throw std::runtime_error("xeFunctionSetArgumentValue failed: " + result);
    }
    if (verbose)
        std::cout << "Input buffer set as function argument\n";

    result = xeFunctionSetArgumentValue(function, 1, sizeof(output), &output);
    if (result) {
        throw std::runtime_error("xeFunctionSetArgumentValue failed: " + result);
    }
    if (verbose)
        std::cout << "Output buffer set as function argument\n";
}

void XePeak::xe_peak_global_bw(L0Context &context) {
    float timed_lo, timed_go, timed, gbps;
    xe_result_t result = XE_RESULT_SUCCESS;
    xe_module_desc_t module_description;
    uint64_t temp_global_size, max_total_work_items;

    std::vector<uint8_t> binary_file =
        context.load_binary_file("xe_global_bw.spv");

    module_description.version = XE_MODULE_DESC_VERSION_CURRENT;
    module_description.format = XE_MODULE_FORMAT_IL_SPIRV;
    module_description.inputSize = static_cast<uint32_t>(binary_file.size());
    // TODO: Remove cast when pInputModule will be declared as uint8_t
    module_description.pInputModule =
        reinterpret_cast<const char *>(binary_file.data());
    module_description.pBuildFlags = nullptr;

    result = xeDeviceCreateModule(context.device, &module_description, &context.module, nullptr);
    if (result) {
        throw std::runtime_error("xeDeviceCreateModule failed: " + result);
    }
    if (verbose)
        std::cout << "Module created\n";

    uint64_t maxItems = MAX_DEVICE_OBJECT_SIZE /
                        sizeof(float) / 2;
    uint64_t numItems = roundToMultipleOf(maxItems,
                                          (context.device_compute_property.maxGroupSizeX * FETCH_PER_WI * 16),
                                          global_bw_max_size);

    std::vector<float> arr(numItems);
    for (int i = 0; i < numItems; i++) {
        arr[i] = static_cast<float>(i);
    }

    void *inputBuf;
    result = xeMemAlloc(context.allocator, context.device,
                        XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                        (numItems * sizeof(float)), 1, &inputBuf);
    if (result) {
        throw std::runtime_error("xeMemAlloc failed: " + result);
    }
    if (verbose)
        std::cout << "inputBuf device arg allocated";

    void *outputBuf;
    result = xeMemAlloc(context.allocator, context.device,
                        XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                        (numItems * sizeof(float)), 1, &outputBuf);
    if (result) {
        throw std::runtime_error("xeMemAlloc failed: " + result);
    }
    if (verbose)
        std::cout << "outputBuf device arg allocated";

    result = xeCommandListAppendMemoryCopy(context.command_list, inputBuf,
                                           arr.data(), (arr.size() * sizeof(float)));
    if (result) {
        throw std::runtime_error("xeCommandListAppendMemoryCopy failed: " + result);
    }
    if (verbose)
        std::cout << "Input buffer copy encoded";

    result = xeCommandListAppendExecutionBarrier(context.command_list);
    if (result) {
        throw std::runtime_error("xeCommandListAppendExecutionBarrier failed: " +
                                 result);
    }
    if (verbose)
        std::cout << "Execution barrier appended";

    result = xeCommandListClose(context.command_list);
    if (result) {
        throw std::runtime_error("xeCommandListClose failed: " + result);
    }
    if (verbose)
        std::cout << "Command list closed";

    result = xeCommandQueueExecuteCommandLists(context.command_queue, 1,
                                               &context.command_list, nullptr);
    if (result) {
        throw std::runtime_error("xeCommandQueueExecuteCommandLists failed: " +
                                 result);
    }
    if (verbose)
        std::cout << "Command list enqueued";

    result = xeCommandQueueSynchronize(context.command_queue, UINT32_MAX);
    if (result) {
        throw std::runtime_error("xeCommandQueueSynchronize failed: " + result);
    }
    if (verbose)
        std::cout << "Command queue synchronized";

    context.reset_commandlist();

    /*Begin setup of Function*/

    xe_function_handle_t local_offset_v1;
    peak_global_bw_setup_function(
        context, local_offset_v1, "global_bandwidth_v1_local_offset", inputBuf,
        outputBuf);
    xe_function_handle_t global_offset_v1;
    peak_global_bw_setup_function(
        context, global_offset_v1, "global_bandwidth_v1_global_offset", inputBuf,
        outputBuf);
    xe_function_handle_t local_offset_v2;
    peak_global_bw_setup_function(
        context, local_offset_v2, "global_bandwidth_v2_local_offset", inputBuf,
        outputBuf);
    xe_function_handle_t global_offset_v2;
    peak_global_bw_setup_function(
        context, global_offset_v2, "global_bandwidth_v2_global_offset", inputBuf,
        outputBuf);
    xe_function_handle_t local_offset_v4;
    peak_global_bw_setup_function(
        context, local_offset_v4, "global_bandwidth_v4_local_offset", inputBuf,
        outputBuf);
    xe_function_handle_t global_offset_v4;
    peak_global_bw_setup_function(
        context, global_offset_v4, "global_bandwidth_v4_global_offset", inputBuf,
        outputBuf);
    xe_function_handle_t local_offset_v8;
    peak_global_bw_setup_function(
        context, local_offset_v8, "global_bandwidth_v8_local_offset", inputBuf,
        outputBuf);
    xe_function_handle_t global_offset_v8;
    peak_global_bw_setup_function(
        context, global_offset_v8, "global_bandwidth_v8_global_offset", inputBuf,
        outputBuf);
    xe_function_handle_t local_offset_v16;
    peak_global_bw_setup_function(
        context, local_offset_v16, "global_bandwidth_v16_local_offset", inputBuf,
        outputBuf);
    xe_function_handle_t global_offset_v16;
    peak_global_bw_setup_function(
        context, global_offset_v16, "global_bandwidth_v16_global_offset",
        inputBuf, outputBuf);

    std::cout << "Global memory bandwidth (GBPS)\n";

    ///////////////////////////////////////////////////////////////////////////
    // Vector width 1
    std::cout << "float   : \n";

    // Run 2 kind of bandwidth kernel
    // lo -- local_size offset - subsequent fetches at local_size offset
    // go -- global_size offset
    temp_global_size = (numItems / FETCH_PER_WI);
    max_total_work_items = convert_cl_to_xe_work_item_count(temp_global_size, context.device_compute_property.maxGroupSizeX);

    timed_lo = run_kernel(context, local_offset_v1, max_total_work_items, iters);
    timed_go = run_kernel(context, global_offset_v1, max_total_work_items, iters);
    timed = (timed_lo < timed_go) ? timed_lo : timed_go;

    gbps = ((float)numItems * sizeof(float)) / timed / 1e3f;

    std::cout << "GBPS: " << gbps << "\n";
    ///////////////////////////////////////////////////////////////////////////

    // Vector width 2
    std::cout << "float2   : \n";

    temp_global_size = (numItems / 2 / FETCH_PER_WI);
    max_total_work_items = convert_cl_to_xe_work_item_count(temp_global_size, context.device_compute_property.maxGroupSizeX);

    timed_lo = run_kernel(context, local_offset_v2, max_total_work_items, iters);
    timed_go = run_kernel(context, global_offset_v2, max_total_work_items, iters);
    timed = (timed_lo < timed_go) ? timed_lo : timed_go;

    gbps = ((float)numItems * sizeof(float)) / timed / 1e3f;

    std::cout << "GBPS: " << gbps << "\n";
    ///////////////////////////////////////////////////////////////////////////

    // Vector width 4
    std::cout << "float4   : \n";

    temp_global_size = (numItems / 4 / FETCH_PER_WI);
    max_total_work_items = convert_cl_to_xe_work_item_count(temp_global_size, context.device_compute_property.maxGroupSizeX);

    timed_lo = run_kernel(context, local_offset_v4, max_total_work_items, iters);
    timed_go = run_kernel(context, global_offset_v4, max_total_work_items, iters);
    timed = (timed_lo < timed_go) ? timed_lo : timed_go;

    gbps = ((float)numItems * sizeof(float)) / timed / 1e3f;

    std::cout << "GBPS: " << gbps << "\n";
    ///////////////////////////////////////////////////////////////////////////

    // Vector width 8
    std::cout << "float8   : \n";

    temp_global_size = (numItems / 8 / FETCH_PER_WI);
    max_total_work_items = convert_cl_to_xe_work_item_count(temp_global_size, context.device_compute_property.maxGroupSizeX);

    timed_lo = run_kernel(context, local_offset_v8, max_total_work_items, iters);
    timed_go = run_kernel(context, global_offset_v8, max_total_work_items, iters);
    timed = (timed_lo < timed_go) ? timed_lo : timed_go;

    gbps = ((float)numItems * sizeof(float)) / timed / 1e3f;

    std::cout << "GBPS: " << gbps << "\n";
    ///////////////////////////////////////////////////////////////////////////

    // Vector width 16
    std::cout << "float16   : \n";
    temp_global_size = (numItems / 16 / FETCH_PER_WI);
    max_total_work_items = convert_cl_to_xe_work_item_count(temp_global_size, context.device_compute_property.maxGroupSizeX);

    timed_lo = run_kernel(context, local_offset_v16, max_total_work_items, iters);
    timed_go = run_kernel(context, global_offset_v16, max_total_work_items, iters);
    timed = (timed_lo < timed_go) ? timed_lo : timed_go;

    gbps = ((float)numItems * sizeof(float)) / timed / 1e3f;

    std::cout << "GBPS: " << gbps << "\n";
}
