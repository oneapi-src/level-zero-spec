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
#include <algorithm>

#define ONE_KB   (1 * 1024ULL)
#define EIGHT_KB (8 * ONE_KB)
#define ONE_MB   (1 * 1024ULL * ONE_KB)
#define FOUR_GB  (4 * 1024ULL * ONE_MB)

//---------------------------------------------------------------------
// Utility function to load the binary spv file from a path
// and return the file as a vector for use by L0.
//---------------------------------------------------------------------
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

//---------------------------------------------------------------------
// Utility function to reset the Command List.
//---------------------------------------------------------------------
void L0Context::reset_commandlist() {
    xe_result_t result = XE_RESULT_SUCCESS;

    result = xeCommandListReset(command_list);
    if (result) {
        throw std::runtime_error("xeCommandListReset failed: " + result);
    }
    if (verbose)
        std::cout << "Command list reset\n";
}

//---------------------------------------------------------------------
// Utility function to create the L0 module from a binary file.
// If successful, this function will set the context's module
// handle to a valid value for use in future calls.
// On error, an exception will be thrown describing the failure.
//---------------------------------------------------------------------
void L0Context::create_module(std::vector<uint8_t> binary_file) {
    xe_result_t result = XE_RESULT_SUCCESS;
    xe_module_desc_t module_description;

    module_description.version = XE_MODULE_DESC_VERSION_CURRENT;
    module_description.format = XE_MODULE_FORMAT_IL_SPIRV;
    module_description.inputSize = static_cast<uint32_t>(binary_file.size());
    // TODO: Remove cast when pInputModule will be declared as uint8_t
    module_description.pInputModule = reinterpret_cast<const uint8_t *>(binary_file.data());
    module_description.pBuildFlags = nullptr;

    result = xeModuleCreate(device, &module_description, &module, nullptr);
    if (result) {
        throw std::runtime_error("xeDeviceCreateModule failed: " + result);
    }
    if (verbose)
        std::cout << "Module created\n";
}

//---------------------------------------------------------------------
// Utility function to print the device properties from xeDeviceGetProperties.
//---------------------------------------------------------------------
void L0Context::print_xe_device_properties(const xe_device_properties_t &props) {
    std::cout << "Device : \n"
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
              //<< " * numComputeCores : " << props.numComputeCores << "\n"
              << " * maxCommandQueuePriority : " << props.maxCommandQueuePriority << std::endl;
}

//---------------------------------------------------------------------
// Utility function to initialize the xe driver, device, command list,
// command queue, & device property information.
// On error, an exception will be thrown describing the failure.
//---------------------------------------------------------------------
void L0Context::init_xe() {
    xe_command_list_desc_t command_list_description;
    xe_command_queue_desc_t command_queue_description;
    xe_result_t result = XE_RESULT_SUCCESS;

    result = xeInit(XE_INIT_FLAG_NONE);
    if (result) {
        throw std::runtime_error("xeDriverInit failed: " + result);
    }
    if (verbose)
        std::cout << "Driver initialized\n";

    result = xeDeviceGetCount(&device_count);
    if (result) {
        throw std::runtime_error("xeDriverGetDeviceCount failed: " + result);
    }
    if (verbose)
        std::cout << "Device count retrieved\n";

    result = xeDeviceGet(0, &device);
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

    result = xeCommandListCreate(device, &command_list_description, &command_list);
    if (result) {
        throw std::runtime_error("xeDeviceCreateCommandList failed: " + result);
    }
    if (verbose)
        std::cout << "command_list created\n";

    command_queue_description.version = XE_COMMAND_QUEUE_DESC_VERSION_CURRENT;
    command_queue_description.ordinal = command_queue_id;
    command_queue_description.mode = XE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;

    result = xeCommandQueueCreate(device, &command_queue_description, &command_queue);
    if (result) {
        throw std::runtime_error("xeDeviceCreateCommandQueue failed: " + result);
    }
    if (verbose)
        std::cout << "Command queue created\n";
}

//---------------------------------------------------------------------
// Utility function to close the command list & command queue.
// On error, an exception will be thrown describing the failure.
//---------------------------------------------------------------------
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

//---------------------------------------------------------------------
// Utility function to execute the command list & synchronize
// the command queue. This function will reset the command list once the
// queue has been synchronized indicating that the commands in the command
// list have been completed.
// On error, an exception will be thrown describing the failure.
//---------------------------------------------------------------------
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

//---------------------------------------------------------------------
// Utility function to convert a global work size and a local work size
// into the number of work items that would be executed with OpenCL.
//---------------------------------------------------------------------
uint64_t XePeak::convert_cl_to_xe_work_item_count(uint64_t global_work_size, uint64_t local_size) {
    uint64_t number_of_workgroups = global_work_size / local_size;
    return number_of_workgroups * (local_size + local_size + local_size);
}

//---------------------------------------------------------------------
// Utility function to total the current work items that would be
// executed given x,y,z sizes and x,y,z counts for the workgroups.
//---------------------------------------------------------------------
uint64_t total_current_work_items(uint64_t group_size_x, uint64_t group_count_x,
                                  uint64_t group_size_y, uint64_t group_count_y,
                                  uint64_t group_size_z, uint64_t group_count_z) {
    return (group_size_x * group_count_x * group_size_y * group_count_y * group_size_z *
            group_count_z);
}

//---------------------------------------------------------------------
// Utility function to set the workgroup dimensions based on the desired
// number of work items a user wants to execute.
// This will attempt to distribute the work items across the workgroup
// dimensions and get to as close to the work items requested as possible.
// Once the number of work items that would be executed is equal to or >
// the number of work items requested, then the workgroup information
// is set accordingly and the total work items that will execute is returned.
//---------------------------------------------------------------------
uint64_t XePeak::set_workgroups(L0Context &context, const uint64_t total_work_items_requested,
                                struct XeWorkGroups *workgroup_info) {

    auto group_size_x = std::min(total_work_items_requested, uint64_t(context.device_compute_property.maxGroupSizeX));
    auto group_size_y = 1;
    auto group_size_z = 1;
    auto group_size = group_size_x * group_size_y * group_size_z;

    auto group_count_x = total_work_items_requested / group_size;
    group_count_x = std::min(group_count_x, uint64_t(context.device_compute_property.maxGroupCountX));
    auto remaining_items = total_work_items_requested - group_count_x * group_size;

    uint64_t group_count_y = remaining_items / (group_count_x * group_size);
    group_count_y = std::min(group_count_y, uint64_t(context.device_compute_property.maxGroupCountY));
    group_count_y = std::max(group_count_y, uint64_t(1));
    remaining_items = total_work_items_requested - group_count_x * group_count_y * group_size;

    uint64_t group_count_z = remaining_items / (group_count_x * group_count_y * group_size);
    group_count_z = std::min(group_count_z, uint64_t(context.device_compute_property.maxGroupCountZ));
    group_count_z = std::max(group_count_z, uint64_t(1));

    auto final_work_items = group_count_x * group_count_y * group_count_z * group_size;
    remaining_items = total_work_items_requested - final_work_items;

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

//---------------------------------------------------------------------
// Utility function to execute the command lists and sync the command queue.
// On error, an exception will be thrown describing the failure.
//---------------------------------------------------------------------
void XePeak::run_command_queue(L0Context &context) {
    xe_result_t result = XE_RESULT_SUCCESS;
    result =
        xeCommandQueueExecuteCommandLists(context.command_queue, 1, &context.command_list, nullptr);
    if (result) {
        throw std::runtime_error("xeCommandQueueExecuteCommandLists failed: " + result);
    }

    result = xeCommandQueueSynchronize(context.command_queue, UINT32_MAX);
    if (result) {
        throw std::runtime_error("xeCommandQueueSynchronize failed: " + result);
    }
}

void single_event_pool_create(L0Context &context,
                              xe_event_pool_handle_t *kernel_launch_event_pool) {
    xe_result_t result;
    xe_event_pool_desc_t kernel_launch_event_pool_desc;

    kernel_launch_event_pool_desc.count = 1;
    kernel_launch_event_pool_desc.flags = XE_EVENT_POOL_FLAG_HOST_VISIBLE;
    kernel_launch_event_pool_desc.version = XE_EVENT_POOL_DESC_VERSION_CURRENT;

    result = xeEventPoolCreate(context.device, &kernel_launch_event_pool_desc,
                               kernel_launch_event_pool);
    if (result) {
        throw std::runtime_error("xeEventPoolCreate failed: " + result);
    }
}

void single_event_create(xe_event_pool_handle_t event_pool,
                         xe_event_handle_t *event) {
        xe_result_t result;
        xe_event_desc_t event_desc;

        event_desc.index = 0;
        event_desc.signal = XE_EVENT_SCOPE_FLAG_NONE;
        event_desc.wait = XE_EVENT_SCOPE_FLAG_NONE;
        event_desc.version = XE_EVENT_DESC_VERSION_CURRENT;
        result = xeEventCreate(event_pool, &event_desc, event);
        if (result) {
            throw std::runtime_error("xeEventCreate failed: " + result);
        }
}
//---------------------------------------------------------------------
// Utility function to execute a kernel function for a set of iterations
// and measure the time elapsed based off the timing type.
// This function takes a pre-calculated workgroup distribution
// and will time the kernel executed given the timing type.
// The current timing types supported are:
//          BANDWIDTH -> Average time to execute the kernel for # iterations
//          KERNEL_LAUNCH_LATENCY -> Average time to execute the kernel on
//                                  the command list
//          KERNEL_COMPLETE_LATENCY - Average time to execute a given kernel
//                                  for # iterations.
// On success, the average time is returned.
// On error, an exception will be thrown describing the failure.
//---------------------------------------------------------------------
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

    /* TODO: implement timing with event profiling for all cases*/

    Timer timer;

    if (type == TimingMeasurement::BANDWIDTH) {
        result = xeCommandListAppendLaunchFunction(context.command_list, function,
                                                   &workgroup_info.thread_group_dimensions, nullptr, 0, nullptr);
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

        for (uint32_t i = 0; i < warmup_iterations; i++) {
            run_command_queue(context);
        }

        timer.start();
        for (uint32_t i = 0; i < iters; i++) {
            run_command_queue(context);
        }
        timed = timer.stopAndTime();
    } else if (type == TimingMeasurement::BANDWIDTH_EVENT_TIMING) {
        xe_event_pool_handle_t event_pool;
        xe_event_handle_t function_event;

        single_event_pool_create(context, &event_pool);
        if (verbose)
            std::cout << "Event Pool Created\n";

        single_event_create(event_pool, &function_event);
        if (verbose)
            std::cout << "Event Created\n";

        result = xeCommandListAppendLaunchFunction(context.command_list,
                                                   function,
                                                   &workgroup_info.thread_group_dimensions,
                                                   function_event, 0, nullptr);
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

        for (uint32_t i = 0; i < warmup_iterations; i++) {
            result = xeCommandQueueExecuteCommandLists(context.command_queue, 1,
                                                       &context.command_list,
                                                       nullptr);
            if (result) {
                throw std::runtime_error(
                        "xeCommandQueueExecuteCommandLists failed: " + result);
            }

            result = xeEventHostSynchronize(function_event, UINT32_MAX);
            if (result) {
                throw std::runtime_error("xeEventHostSynchronize failed: " +
                                         result);
            }

            result = xeCommandQueueSynchronize(context.command_queue,
                                               UINT32_MAX);
            if (result) {
                throw std::runtime_error("xeCommandQueueSynchronize failed: " +
                                         result);
            }

            result = xeEventReset(function_event);
            if (result) {
                throw std::runtime_error("xeEventReset failed: " + result);
            }
            if (verbose)
                std::cout << "Event Reset" << std::endl;
        }

        for (uint32_t i = 0; i < iters; i++) {
            timer.start();
            result = xeCommandQueueExecuteCommandLists(context.command_queue, 1,
                                                       &context.command_list,
                                                       nullptr);
            if (result) {
                throw std::runtime_error(
                        "xeCommandQueueExecuteCommandLists failed: " + result);
            }

            result = xeEventHostSynchronize(function_event, UINT32_MAX);
            if (result) {
                throw std::runtime_error("xeEventHostSynchronize failed: " +
                                         result);
            }
            timed += timer.stopAndTime();

            result = xeCommandQueueSynchronize(context.command_queue,
                                               UINT32_MAX);
            if (result) {
                throw std::runtime_error("xeCommandQueueSynchronize failed: " +
                                         result);
            }
            if (verbose)
                std::cout << "Command queue synchronized\n";

            result = xeEventReset(function_event);
            if (result) {
                throw std::runtime_error("xeEventReset failed: " + result);
            }
            if (verbose)
                std::cout << "Event Reset\n";
        }
        xeEventDestroy(function_event);
    } else if (type == TimingMeasurement::KERNEL_LAUNCH_LATENCY) {
        xe_event_handle_t kernel_launch_event;
        xe_event_pool_handle_t kernel_launch_event_pool;

        single_event_pool_create(context, &kernel_launch_event_pool);
        if (verbose)
            std::cout << "Event Pool Created\n";

        single_event_create(kernel_launch_event_pool, &kernel_launch_event);
        if (verbose)
            std::cout << "Event Created\n";
        result = xeCommandListAppendSignalEvent(context.command_list, kernel_launch_event);
        if (result) {
            throw std::runtime_error("xeCommandListAppendSignalEvent failed: " + result);
        }
        if (verbose)
            std::cout << "Kernel Launch Event signal appended to command list\n";

        result = xeCommandListAppendLaunchFunction(context.command_list, function,
                                                   &workgroup_info.thread_group_dimensions, nullptr, 0, nullptr);
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

        for (uint32_t i = 0; i < warmup_iterations; i++) {
            run_command_queue(context);
            result = xeEventHostSynchronize(kernel_launch_event, UINT32_MAX);
            if (result) {
                throw std::runtime_error("xeEventHostSynchronize failed: " + result);
            }
            result = xeEventReset(kernel_launch_event);
            if (result) {
                throw std::runtime_error("xeEventReset failed: " + result);
            }
            if (verbose)
                std::cout << "Event Reset\n";
        }

        for (uint32_t i = 0; i < iters; i++) {
            timer.start();
            result = xeCommandQueueExecuteCommandLists(context.command_queue, 1,
                                                       &context.command_list, nullptr);
            if (result) {
                throw std::runtime_error("xeCommandQueueExecuteCommandLists failed: " + result);
            }

            result = xeEventHostSynchronize(kernel_launch_event, UINT32_MAX);
            if (result) {
                throw std::runtime_error("xeEventHostSynchronize failed: " + result);
            }
            timed += timer.stopAndTime();

            result = xeCommandQueueSynchronize(context.command_queue, UINT32_MAX);
            if (result) {
                throw std::runtime_error("xeCommandQueueSynchronize failed: " + result);
            }
            if (verbose)
                std::cout << "Command queue synchronized\n";

            result = xeEventReset(kernel_launch_event);
            if (result) {
                throw std::runtime_error("xeEventReset failed: " + result);
            }
            if (verbose)
                std::cout << "Event Reset\n";
        }
    } else if (type == TimingMeasurement::KERNEL_COMPLETE_LATENCY) {
        result = xeCommandListAppendLaunchFunction(context.command_list, function,
                                                   &workgroup_info.thread_group_dimensions, nullptr, 0, nullptr);
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

        for (uint32_t i = 0; i < warmup_iterations; i++) {
            run_command_queue(context);
        }

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

//---------------------------------------------------------------------
// Utility function to setup a kernel function with an input & output argument.
// On error, an exception will be thrown describing the failure.
//---------------------------------------------------------------------
void XePeak::setup_function(L0Context &context, xe_function_handle_t &function, const char *name,
                            void *input, void *output) {
    xe_function_desc_t function_description;
    xe_result_t result = XE_RESULT_SUCCESS;

    function_description.version = XE_FUNCTION_DESC_VERSION_CURRENT;
    function_description.flags = XE_FUNCTION_FLAG_NONE;
    function_description.pFunctionName = name;

    result = xeFunctionCreate(context.module, &function_description, &function);
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

//---------------------------------------------------------------------
// Utility function to calculate the max work items that the current
// device can execute simultaneously with a single kernel function enqueued.
//---------------------------------------------------------------------
uint64_t XePeak::get_max_work_items(L0Context &context) {
    return context.device_property.numSlicesPerTile *
           context.device_property.numSubslicesPerSlice *
           context.device_property.numEUsPerSubslice *
           context.device_compute_property.maxGroupSizeX;
}

//---------------------------------------------------------------------
// Utility function to print a standard string to end a test.
//---------------------------------------------------------------------
void XePeak::print_test_complete() { std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"; }

//---------------------------------------------------------------------
// Main function which calls the argument parsing and calls each
// test requested.
//---------------------------------------------------------------------
int main(int argc, char **argv) {
    XePeak peak_benchmark;
    L0Context context;

    peak_benchmark.parse_arguments(argc, argv);
    context.verbose = peak_benchmark.verbose;

    context.init_xe();

    if (peak_benchmark.run_global_bw)
        peak_benchmark.xe_peak_global_bw(context);

    if (peak_benchmark.run_hp_compute)
        peak_benchmark.xe_peak_hp_compute(context);

    if (peak_benchmark.run_sp_compute)
        peak_benchmark.xe_peak_sp_compute(context);

    if (peak_benchmark.run_dp_compute)
        peak_benchmark.xe_peak_dp_compute(context);

    if (peak_benchmark.run_int_compute)
        peak_benchmark.xe_peak_int_compute(context);

    if (peak_benchmark.run_transfer_bw)
        peak_benchmark.xe_peak_transfer_bw(context);

    if (peak_benchmark.run_kernel_lat)
        peak_benchmark.xe_peak_kernel_latency(context);

    context.clean_xe();

    return 0;
}

#if defined(unix) || defined(__unix__) || defined(__unix)

#include <unistd.h>

unsigned long long int total_available_memory()
{
    const long page_count = sysconf(_SC_PHYS_PAGES);
    const long page_size  = sysconf(_SC_PAGE_SIZE);
    const unsigned long long total_bytes = page_count * page_size;

    return total_bytes;
}

#endif

#if defined(_WIN64) || defined(_WIN64)

#define NOMINMAX
#include <windows.h>

unsigned long long int total_available_memory()
{
    MEMORYSTATUSEX stat;
    stat.dwLength = sizeof(stat);
    GlobalMemoryStatusEx(&stat);

    return stat.ullAvailVirtual;
}

#endif

inline bool is_integrated_gpu(xe_device_properties_t &device_properties) {
    return (device_properties.totalLocalMemSize == 0);
}

uint64_t max_device_object_size(L0Context &context) {
    xe_result_t result;

    xe_device_properties_t device_properties =
        {XE_DEVICE_PROPERTIES_VERSION_CURRENT};

    result = xeDeviceGetProperties(context.device, &device_properties);
    if (result) {
        throw std::runtime_error("xeDeviceGetProperties failed: " + result);
    }

    if (is_integrated_gpu(device_properties)) {
        unsigned long long int total_memory = total_available_memory();
        if (total_memory > FOUR_GB) {
            return FOUR_GB - EIGHT_KB;
        } else {
            return std::max(total_memory / 4, 128 * ONE_MB);
        }
    } else {
        return device_properties.totalLocalMemSize;
    }
}

TimingMeasurement XePeak::is_bandwidth_with_event_timer(void) {
    if (use_event_timer) {
        return TimingMeasurement::BANDWIDTH_EVENT_TIMING;
    } else {
        return TimingMeasurement::BANDWIDTH;
    }
}
