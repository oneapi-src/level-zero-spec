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

std::vector<uint8_t> L0Context::load_binary_file(const std::string &file_path) {
    if (verbose)
        std::cout << "File path: " << file_path << "\n";
    std::ifstream stream(file_path, std::ios::in | std::ios::binary);

    std::vector<uint8_t> binary_file;
    if (!stream.good()) {
        std::cerr << "Failed to load binary file: " << file_path << "\n";
        return binary_file;
    }

    size_t length = 0;
    stream.seekg(0, stream.end);
    length = static_cast<size_t>(stream.tellg());
    stream.seekg(0, stream.beg);
    if (verbose)
        std::cout << "Binary file length: " << length << "\n";

    binary_file.resize(length);
    stream.read(reinterpret_cast<char *>(binary_file.data()), length);
    if (verbose)
        std::cout << "Binary file loaded"
                  << "\n";

    return binary_file;
}

void L0Context::reset_commandlist() {
    xe_result_t result = XE_RESULT_SUCCESS;

#if 0
    result = xeCommandListReset(command_list);
    if (result) {
        throw std::runtime_error("xeCommandListReset failed: " + result);
    }
    if (verbose)
        std::cout << "Command list reset\n";
#else
    xe_command_list_desc_t command_list_description;
    if (command_list) {
        result = xeCommandListDestroy(command_list);
        if (result) {
            throw std::runtime_error("xeCommandListDestroy failed: " + result);
        }
        if (verbose)
            std::cout << "Command list destroyed\n";
    }

    command_list_description.version = XE_COMMAND_LIST_DESC_VERSION_CURRENT;

    result = xeDeviceCreateCommandList(device, &command_list_description, &command_list);
    if (result) {
        throw std::runtime_error("xeDeviceCreateCommandList failed: " + result);
    }
    if (verbose)
        std::cout << "command_list created\n";
#endif
}

void L0Context::create_module(std::vector<uint8_t> binary_file) {
    xe_result_t result = XE_RESULT_SUCCESS;
    xe_module_desc_t module_description;

    module_description.version = XE_MODULE_DESC_VERSION_CURRENT;
    module_description.format = XE_MODULE_FORMAT_IL_SPIRV;
    module_description.inputSize = static_cast<uint32_t>(binary_file.size());
    // TODO: Remove cast when pInputModule will be declared as uint8_t
    module_description.pInputModule = reinterpret_cast<const char *>(binary_file.data());
    module_description.pBuildFlags = nullptr;

    result = xeDeviceCreateModule(device, &module_description, &module, nullptr);
    if (result) {
        throw std::runtime_error("xeDeviceCreateModule failed: " + result);
    }
    if (verbose)
        std::cout << "Module created\n";
}

void L0Context::print_xe_device_properties(const xe_device_properties_t &props) {
    std::cout << "Device : "
              << "\n"
              << " * name : " << props.name << "\n"
              << " * vendorId : " << props.vendorId << "\n"
              << " * deviceId : " << props.deviceId << "\n"
              << " * subdeviceId : " << props.subdeviceId << "\n"
              << " * isSubdevice : " << (props.isSubdevice ? "TRUE" : "FALSE") << "\n"
              << " * numSubDevices : " << props.numSubDevices << "\n"
              << " * coreClockRate : " << props.coreClockRate << "\n"
              << " * memClockRate : " << props.memClockRate << "\n"
              << " * memGlobalBusWidth : " << props.memGlobalBusWidth << "\n"
              << " * totalLocalMemSize : " << props.totalLocalMemSize << "\n"
              << " * numAsyncComputeEngines : " << props.numAsyncComputeEngines << "\n"
              << " * numAsyncCopyEngines  : " << props.numAsyncCopyEngines << "\n"
              << " * numComputeCores : " << props.numComputeCores << "\n"
              << " * maxCommandQueuePriority : " << props.maxCommandQueuePriority << std::endl;
}

void L0Context::init_xe() {
    xe_command_list_desc_t command_list_description;
    xe_command_queue_desc_t command_queue_description;
    xe_result_t result = XE_RESULT_SUCCESS;

    result = xeDriverInit(XE_INIT_FLAG_NONE);
    if (result) {
        throw std::runtime_error("xeDriverInit failed: " + result);
    }
    if (verbose)
        std::cout << "Driver initialized\n";

    result = xeDriverGetDeviceCount(&device_count);
    if (result) {
        throw std::runtime_error("xeDriverGetDeviceCount failed: " + result);
    }
    if (verbose)
        std::cout << "Device count retrieved\n";

    std::vector<xe_device_uuid_t> uuids(device_count);
    result = xeDriverGetDeviceUniqueIds(device_count, uuids.data());
    if (result) {
        throw std::runtime_error("xeDriverGetDeviceUniqueIds failed: " + result);
    }
    if (verbose)
        std::cout << "Device UUIDs retrieved\n";

    result = xeDriverGetDevice(&uuids[default_device], &device);
    if (result) {
        throw std::runtime_error("xeDriverGetDevice failed: " + result);
    }
    if (verbose)
        std::cout << "Device retrieved\n";

    device_property.version = XE_DEVICE_PROPERTIES_VERSION_CURRENT;
    result = xeDeviceGetProperties(device, &device_property);
    if (result) {
        throw std::runtime_error("xeDeviceGetProperties failed: " + result);
    }
    if (verbose)
        std::cout << "Device Properties retrieved\n";

    print_xe_device_properties(device_property);

    device_compute_property.version = XE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT;
    result = xeDeviceGetComputeProperties(device, &device_compute_property);
    if (result) {
        throw std::runtime_error("xeDeviceGetComputeProperties failed: " + result);
    }
    if (verbose)
        std::cout << "Device Compute Properties retrieved\n";

    command_list_description.version = XE_COMMAND_LIST_DESC_VERSION_CURRENT;

    result = xeDeviceCreateCommandList(device, &command_list_description, &command_list);
    if (result) {
        throw std::runtime_error("xeDeviceCreateCommandList failed: " + result);
    }
    if (verbose)
        std::cout << "command_list created\n";

    command_queue_description.version = XE_COMMAND_QUEUE_DESC_VERSION_CURRENT;
    command_queue_description.ordinal = command_queue_id;
    command_queue_description.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;

    result = xeDeviceCreateCommandQueue(device, &command_queue_description, &command_queue);
    if (result) {
        throw std::runtime_error("xeDeviceCreateCommandQueue failed: " + result);
    }
    if (verbose)
        std::cout << "Command queue created\n";
}

void L0Context::clean_xe() {
    xe_result_t result = XE_RESULT_SUCCESS;

    result = xeCommandQueueDestroy(command_queue);
    if (result) {
        throw std::runtime_error("xeCommandQueueDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "Command queue destroyed\n";

    result = xeCommandListDestroy(command_list);
    if (result) {
        throw std::runtime_error("xeCommandListDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "command_list destroyed\n";
}

void L0Context::execute_commandlist_and_sync() {
    xe_result_t result = XE_RESULT_SUCCESS;

    result = xeCommandListClose(command_list);
    if (result) {
        throw std::runtime_error("xeCommandListClose failed: " + result);
    }
    if (verbose)
        std::cout << "Command list closed\n";

    result = xeCommandQueueExecuteCommandLists(command_queue, 1, &command_list, nullptr);
    if (result) {
        throw std::runtime_error("xeCommandQueueExecuteCommandLists failed: " + result);
    }
    if (verbose)
        std::cout << "Command list enqueued\n";

    result = xeCommandQueueSynchronize(command_queue, UINT32_MAX);
    if (result) {
        throw std::runtime_error("xeCommandQueueSynchronize failed: " + result);
    }
    if (verbose)
        std::cout << "Command queue synchronized\n";

    reset_commandlist();
}

uint64_t XePeak::convert_cl_to_xe_work_item_count(uint64_t global_work_size, uint64_t local_size) {
    uint64_t number_of_workgroups = global_work_size / local_size;
    return number_of_workgroups * (local_size + local_size + local_size);
}

uint64_t total_current_work_items(uint64_t group_size_x, uint64_t group_count_x,
                                  uint64_t group_size_y, uint64_t group_count_y,
                                  uint64_t group_size_z, uint64_t group_count_z) {
    return (group_size_x * group_count_x * group_size_y * group_count_y * group_size_z *
            group_count_z);
}

uint64_t XePeak::set_workgroups(L0Context &context, const uint64_t total_work_items_requested,
                                struct XeWorkGroups *workgroup_info) {

    uint64_t final_work_items = 0;
    uint64_t group_count_x = 1;
    uint64_t group_count_y = 1;
    uint64_t group_count_z = 1;
    uint64_t group_size_x = 1;
    uint64_t group_size_y = 1;
    uint64_t group_size_z = 1;

    while (final_work_items < total_work_items_requested) {
        if (group_count_x < context.device_compute_property.maxGroupCountX) {
            group_count_x += 1;
            final_work_items = total_current_work_items(group_size_x, group_count_x, group_size_y,
                                                        group_count_y, group_size_z, group_count_z);
        }
        if ((group_count_y < context.device_compute_property.maxGroupCountY) &&
            final_work_items < total_work_items_requested) {
            group_count_y += 1;
            final_work_items = total_current_work_items(group_size_x, group_count_x, group_size_y,
                                                        group_count_y, group_size_z, group_count_z);
        }
        if ((group_count_z < context.device_compute_property.maxGroupCountZ) &&
            final_work_items < total_work_items_requested) {
            group_count_z += 1;
            final_work_items = total_current_work_items(group_size_x, group_count_x, group_size_y,
                                                        group_count_y, group_size_z, group_count_z);
        }
        if ((final_work_items < total_work_items_requested) &&
            (group_size_x < context.device_compute_property.maxGroupSizeX)) {
            group_size_x += 1;
            final_work_items = total_current_work_items(group_size_x, group_count_x, group_size_y,
                                                        group_count_y, group_size_z, group_count_z);
        }
        if ((final_work_items < total_work_items_requested) &&
            (group_size_y < context.device_compute_property.maxGroupSizeY)) {
            group_size_y += 1;
            final_work_items = total_current_work_items(group_size_x, group_count_x, group_size_y,
                                                        group_count_y, group_size_z, group_count_z);
        }
        if ((final_work_items < total_work_items_requested) &&
            (group_size_z < context.device_compute_property.maxGroupSizeZ)) {
            group_size_z += 1;
            final_work_items = total_current_work_items(group_size_x, group_count_x, group_size_y,
                                                        group_count_y, group_size_z, group_count_z);
        }
    }

    if (verbose) {
        std::cout << "Group size x: " << group_size_x << "\n";
        std::cout << "Group size y: " << group_size_y << "\n";
        std::cout << "Group size z: " << group_size_z << "\n";
        std::cout << "Group count x: " << group_count_x << "\n";
        std::cout << "Group count y: " << group_count_y << "\n";
        std::cout << "Group count z: " << group_count_z << "\n";
    }

    if (verbose)
        std::cout << "total work items that will be executed: " << final_work_items
                  << " requested: " << total_work_items_requested << "\n";

    workgroup_info->group_size_x = static_cast<uint32_t>(group_size_x);
    workgroup_info->group_size_y = static_cast<uint32_t>(group_size_y);
    workgroup_info->group_size_z = static_cast<uint32_t>(group_size_z);
    workgroup_info->thread_group_dimensions.groupCountX = static_cast<uint32_t>(group_count_x);
    workgroup_info->thread_group_dimensions.groupCountY = static_cast<uint32_t>(group_count_y);
    workgroup_info->thread_group_dimensions.groupCountZ = static_cast<uint32_t>(group_count_z);

    return final_work_items;
}

void XePeak::run_command_queue(L0Context &context) {
    xe_result_t result = XE_RESULT_SUCCESS;
    result =
        xeCommandQueueExecuteCommandLists(context.command_queue, 1, &context.command_list, nullptr);
    if (result) {
        throw std::runtime_error("xeCommandQueueExecuteCommandLists failed: " + result);
    }
    if (verbose)
        std::cout << "Command list enqueued\n";

    result = xeCommandQueueSynchronize(context.command_queue, UINT32_MAX);
    if (result) {
        throw std::runtime_error("xeCommandQueueSynchronize failed: " + result);
    }
    if (verbose)
        std::cout << "Command queue synchronized\n";
}

float XePeak::run_kernel(L0Context context, xe_function_handle_t &function,
                         struct XeWorkGroups &workgroup_info, TimingMeasurement type,
                         bool reset_command_list) {
    xe_result_t result = XE_RESULT_SUCCESS;
    float timed = 0;

    result = xeFunctionSetGroupSize(function, workgroup_info.group_size_x,
                                    workgroup_info.group_size_y, workgroup_info.group_size_z);
    if (result) {
        throw std::runtime_error("xeFunctionSetGroupSize failed: " + result);
    }
    if (verbose)
        std::cout << "Group size set\n";

    result = xeCommandListAppendLaunchFunction(context.command_list, function,
                                               &workgroup_info.thread_group_dimensions, nullptr);
    if (result) {
        throw std::runtime_error("xeCommandListAppendLaunchFunction failed: " + result);
    }
    if (verbose)
        std::cout << "Function launch appended\n";

    result = xeCommandListClose(context.command_list);
    if (result) {
        throw std::runtime_error("xeCommandListClose failed: " + result);
    }
    if (verbose)
        std::cout << "Command list closed\n";

    /* TODO: implement timing with xeEventQueryElapsedTime*/

    Timer timer;

    if (type == BANDWIDTH) {
        timer.start();
        for (uint32_t i = 0; i < iters; i++) {
            run_command_queue(context);
        }
        timed = timer.stopAndTime();
    } else if (type == KERNEL_LAUNCH_LATENCY) {
        for (uint32_t i = 0; i < iters; i++) {
            /* TODO: implement timing with xeEventQueryElapsedTime for Launch Latency*/
            timer.start();
            result = xeCommandQueueExecuteCommandLists(context.command_queue, 1,
                                                       &context.command_list, nullptr);
            timed += timer.stopAndTime();
            if (result) {
                throw std::runtime_error("xeCommandQueueExecuteCommandLists failed: " + result);
            }
            if (verbose)
                std::cout << "Command list enqueued\n";

            result = xeCommandQueueSynchronize(context.command_queue, UINT32_MAX);
            if (result) {
                throw std::runtime_error("xeCommandQueueSynchronize failed: " + result);
            }
            if (verbose)
                std::cout << "Command queue synchronized\n";
        }
    } else if (type == KERNEL_COMPLETE_LATENCY) {
        for (uint32_t i = 0; i < iters; i++) {
            timer.start();
            run_command_queue(context);
            timed += timer.stopAndTime();
        }
    }

    if (reset_command_list)
        context.reset_commandlist();

    return (timed / static_cast<float>(iters));
}

void XePeak::setup_function(L0Context &context, xe_function_handle_t &function, const char *name,
                            void *input, void *output) {
    xe_function_desc_t function_description;
    xe_result_t result = XE_RESULT_SUCCESS;

    function_description.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    function_description.flags = XE_FUNCTION_FLAG_NONE;
    function_description.pFunctionName = name;

    result = xeModuleCreateFunction(context.module, &function_description, &function);
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

uint64_t XePeak::get_max_work_items(L0Context &context) {
    uint64_t group_size_x = context.device_compute_property.maxGroupSizeX;
    uint64_t group_size_y = context.device_compute_property.maxGroupSizeY;
    uint64_t group_size_z = context.device_compute_property.maxGroupSizeZ;
    uint64_t group_count_x = context.device_compute_property.maxGroupCountX;
    uint64_t group_count_y = context.device_compute_property.maxGroupCountY;
    uint64_t group_count_z = context.device_compute_property.maxGroupCountZ;

    uint64_t max_work_items = (group_size_x * group_size_y * group_size_z * group_count_x *
                               group_count_y * group_count_z);
    return max_work_items;
}

void XePeak::print_test_complete() { std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"; }

int main(int argc, char **argv) {
    XePeak peak_benchmark;
    L0Context context;

    peak_benchmark.parse_arguments(argc, argv);
    context.verbose = peak_benchmark.verbose;

    context.init_xe();

    if (peak_benchmark.run_global_bw)
        peak_benchmark.xe_peak_global_bw(context);

    if (peak_benchmark.run_sp_compute)
        peak_benchmark.xe_peak_sp_compute(context);

    if (peak_benchmark.run_dp_compute)
        peak_benchmark.xe_peak_dp_compute(context);

    if (peak_benchmark.run_int_compute)
        peak_benchmark.xe_peak_int_compute(context);

    if (peak_benchmark.run_kernel_lat)
        peak_benchmark.xe_peak_kernel_latency(context);

    context.clean_xe();

    return 0;
}
