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
    xe_command_list_desc_t command_list_description;
    xe_result_t result = XE_RESULT_SUCCESS;

    result = xeCommandListDestroy(command_list);
    if (result) {
        throw std::runtime_error("xeCommandListDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "Command list destroyed\n";

    command_list_description.version = XE_COMMAND_LIST_DESC_VERSION_CURRENT;

    result = xeDeviceCreateCommandList(device, &command_list_description, &command_list);
    if (result) {
        throw std::runtime_error("xeDeviceCreateCommandList failed: " + result);
    }
    if (verbose)
        std::cout << "command_list created\n";
}

void L0Context::print_xe_device_properties(const xe_device_properties_t &props) {
    std::cout << "Device : "
              << "\n"
              << " * name : " << props.device_name << "\n"
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
    if (verbose) {
        std::cout << "Device Properties retrieved\n";
        print_xe_device_properties(device_property);
    }

    device_compute_property.version = XE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT;
    result = xeDeviceGetComputeProperties(device, &device_compute_property);
    if (result) {
        throw std::runtime_error("xeDeviceGetComputeProperties failed: " + result);
    }
    if (verbose)
        std::cout << "Device Compute Properties retrieved\n";

    result = xeCreateMemAllocator(&allocator);
    if (result) {
        throw std::runtime_error("xe_mem_allocator_handle_t failed: " + result);
    }
    if (verbose)
        std::cout << "Allocator created\n";

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

    result = xeModuleDestroy(module);
    if (result) {
        throw std::runtime_error("xeModuleDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "Module destroyed\n";

    result = xeMemAllocatorDestroy(allocator);
    if (result) {
        throw std::runtime_error("xeMemAllocatorDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "Allocator destroyed\n";
}

uint64_t XePeak::convert_cl_to_xe_work_item_count(uint64_t global_work_size, uint64_t local_size) {
    uint64_t number_of_workgroups = global_work_size / local_size;
    return number_of_workgroups * (local_size + local_size + local_size);
}

void XePeak::set_workgroups(L0Context &context, const uint64_t total_work_items_requested,
                            uint32_t *group_size_x, uint32_t *group_size_y, uint32_t *group_size_z,
                            xe_thread_group_dimensions_t *thread_group_dimensions) {

    uint64_t final_work_items = 0;
    thread_group_dimensions->groupCountX = 1;
    thread_group_dimensions->groupCountY = 1;
    thread_group_dimensions->groupCountZ = 1;
    *group_size_x = 1;
    *group_size_y = 1;
    *group_size_z = 1;

    while (final_work_items < total_work_items_requested) {
        if (thread_group_dimensions->groupCountX < context.device_compute_property.maxGroupCountX) {
            thread_group_dimensions->groupCountX += 1;
            final_work_items = (*group_size_x * thread_group_dimensions->groupCountX *
                                *group_size_y * thread_group_dimensions->groupCountY *
                                *group_size_z * thread_group_dimensions->groupCountZ);
        }
        if ((thread_group_dimensions->groupCountY <
             context.device_compute_property.maxGroupCountY) &&
            final_work_items < total_work_items_requested) {
            thread_group_dimensions->groupCountY += 1;
            final_work_items = (*group_size_x * thread_group_dimensions->groupCountX *
                                *group_size_y * thread_group_dimensions->groupCountY *
                                *group_size_z * thread_group_dimensions->groupCountZ);
        }
        if ((thread_group_dimensions->groupCountZ <
             context.device_compute_property.maxGroupCountZ) &&
            final_work_items < total_work_items_requested) {
            thread_group_dimensions->groupCountZ += 1;
            final_work_items = (*group_size_x * thread_group_dimensions->groupCountX *
                                *group_size_y * thread_group_dimensions->groupCountY *
                                *group_size_z * thread_group_dimensions->groupCountZ);
        }
        if ((final_work_items < total_work_items_requested) &&
            (*group_size_x < context.device_compute_property.maxGroupSizeX)) {
            *group_size_x += 1;
            final_work_items = (*group_size_x * thread_group_dimensions->groupCountX *
                                *group_size_y * thread_group_dimensions->groupCountY *
                                *group_size_z * thread_group_dimensions->groupCountZ);
        }
        if ((final_work_items < total_work_items_requested) &&
            (*group_size_y < context.device_compute_property.maxGroupSizeY)) {
            *group_size_y += 1;
            final_work_items = (*group_size_x * thread_group_dimensions->groupCountX *
                                *group_size_y * thread_group_dimensions->groupCountY *
                                *group_size_z * thread_group_dimensions->groupCountZ);
        }
        if ((final_work_items < total_work_items_requested) &&
            (*group_size_z < context.device_compute_property.maxGroupSizeZ)) {
            *group_size_z += 1;
            final_work_items = (*group_size_x * thread_group_dimensions->groupCountX *
                                *group_size_y * thread_group_dimensions->groupCountY *
                                *group_size_z * thread_group_dimensions->groupCountZ);
        }
    }

    if (verbose)
        std::cout << "total work items that will be executed: " << final_work_items
                  << " requested: " << total_work_items_requested << "\n";
}

float XePeak::run_kernel(L0Context context, xe_function_handle_t &function,
                         uint64_t total_number_work_items, int iters, TimingMeasurement type) {
    xe_result_t result = XE_RESULT_SUCCESS;
    float timed = 0;

    uint32_t group_size_x = 0;
    uint32_t group_size_y = 0;
    uint32_t group_size_z = 0;
    xe_thread_group_dimensions_t thread_group_dimensions;
    set_workgroups(context, total_number_work_items, &group_size_x, &group_size_y, &group_size_z,
                   &thread_group_dimensions);

    if (verbose) {
        std::cout << "Group size x: " << group_size_x << "\n";
        std::cout << "Group size y: " << group_size_y << "\n";
        std::cout << "Group size z: " << group_size_z << "\n";
        std::cout << "Group count x: " << thread_group_dimensions.groupCountX << "\n";
        std::cout << "Group count y: " << thread_group_dimensions.groupCountY << "\n";
        std::cout << "Group count z: " << thread_group_dimensions.groupCountZ << "\n";
    }

    result = xeFunctionSetGroupSize(function, group_size_x, group_size_y, group_size_z);
    if (result) {
        throw std::runtime_error("xeFunctionSetGroupSize failed: " + result);
    }
    if (verbose)
        std::cout << "Group size set\n";

    result = xeCommandListAppendLaunchFunction(context.command_list, function,
                                               &thread_group_dimensions, nullptr);
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
    }
    for (int i = 0; i < iters; i++) {
        if (type == KERNEL_LAUNCH_LATENCY || type == KERNEL_COMPLETE_LATENCY) {
            timer.start();
        }
        result = xeCommandQueueExecuteCommandLists(context.command_queue, 1, &context.command_list,
                                                   nullptr);
        if (result) {
            throw std::runtime_error("xeCommandQueueExecuteCommandLists failed: " + result);
        }
        if (verbose)
            std::cout << "Command list enqueued\n";
        if (type == KERNEL_LAUNCH_LATENCY) {
            timed += timer.stopAndTime();
        }

        result = xeCommandQueueSynchronize(context.command_queue, UINT32_MAX);
        if (result) {
            throw std::runtime_error("xeCommandQueueSynchronize failed: " + result);
        }
        if (verbose)
            std::cout << "Command queue synchronized\n";
        if (type == KERNEL_COMPLETE_LATENCY) {
            timed += timer.stopAndTime();
        }
    }
    if (type == BANDWIDTH) {
        timed = timer.stopAndTime();
    }

    result = xeFunctionDestroy(function);
    if (result) {
        throw std::runtime_error("xeFunctionDestroy failed: " + result);
    }
    if (verbose)
        std::cout << "Function Destroyed\n";

    return (timed / static_cast<float>(iters));
}

int main(int argc, char **argv) {
    XePeak peak_benchmark;
    L0Context context;

    peak_benchmark.parse_arguments(argc, argv);
    context.verbose = peak_benchmark.verbose;

    context.init_xe();

    if (peak_benchmark.run_global_bw)
        peak_benchmark.xe_peak_global_bw(context);

    context.reset_commandlist();

    if (peak_benchmark.run_kernel_lat)
        peak_benchmark.xe_peak_kernel_latency(context);

    context.clean_xe();

    return 0;
}
