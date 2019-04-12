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
    uint32_t num_items = (context.device_compute_property.maxGroupCountX) *
                         (context.device_property.numComputeCores) * FETCH_PER_WI;
    uint64_t global_size = (num_items / FETCH_PER_WI);
    uint64_t total_work_items = convert_cl_to_xe_work_item_count(
        global_size, context.device_compute_property.maxGroupSizeX);
    float latency = 0;
    xe_result_t result = XE_RESULT_SUCCESS;
    xe_module_desc_t module_description;

    std::vector<uint8_t> binary_file = context.load_binary_file("xe_global_bw.spv");

    module_description.version = XE_MODULE_DESC_VERSION_CURRENT;
    module_description.format = XE_MODULE_FORMAT_IL_SPIRV;
    module_description.inputSize = static_cast<uint32_t>(binary_file.size());
    // TODO: Remove cast when pInputModule will be declared as uint8_t
    module_description.pInputModule = reinterpret_cast<const char *>(binary_file.data());
    module_description.pBuildFlags = nullptr;

    result = xeDeviceCreateModule(context.device, &module_description, &context.module, nullptr);
    if (result) {
        throw std::runtime_error("xeDeviceCreateModule failed: " + result);
    }
    if (verbose)
        std::cout << "Module created\n";

    void *inputBuf;
    result = xeMemAlloc(context.allocator, context.device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                        (num_items * sizeof(float)), 1, &inputBuf);
    if (result) {
        throw std::runtime_error("xeMemAlloc failed: " + result);
    }
    if (verbose)
        std::cout << "inputBuf device buffer allocated\n";

    void *outputBuf;
    result = xeMemAlloc(context.allocator, context.device, XE_DEVICE_MEM_ALLOC_FLAG_DEFAULT,
                        (num_items * sizeof(float)), 1, &outputBuf);
    if (result) {
        throw std::runtime_error("xeMemAlloc failed: " + result);
    }
    if (verbose)
        std::cout << "outputBuf device buffer allocated\n";

    xe_function_handle_t local_offset_v1;
    peak_global_bw_setup_function(context, local_offset_v1, "global_bandwidth_v1_local_offset",
                                  inputBuf, outputBuf);

    std::cout << "Kernel launch latency\n";

    latency = run_kernel(context, local_offset_v1, total_work_items, iters, KERNEL_LAUNCH_LATENCY);

    std::cout << latency << " us\n";

    context.reset_commandlist();
    peak_global_bw_setup_function(context, local_offset_v1, "global_bandwidth_v1_local_offset",
                                  inputBuf, outputBuf);

    std::cout << "Kernel latency\n";

    latency =
        run_kernel(context, local_offset_v1, total_work_items, iters, KERNEL_COMPLETE_LATENCY);

    std::cout << latency << " us\n";

    result = xeMemFree(context.allocator, inputBuf);
    if (result) {
        throw std::runtime_error("xeMemFree failed: " + result);
    }
    if (verbose)
        std::cout << "Input Buffer freed\n";

    result = xeMemFree(context.allocator, outputBuf);
    if (result) {
        throw std::runtime_error("xeMemFree failed: " + result);
    }
    if (verbose)
        std::cout << "Output Buffer freed\n";
}