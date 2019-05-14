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
#include "benchmark.hpp"

using namespace xe_api_benchmarks;

void header_print_iteration(std::string prefix, probe_config_t &probe_setting) {
    std::cout << prefix
              << "\tWarm up iterations " << probe_setting.warm_up_iteration
              << "\tMeasured iterations " << probe_setting.measure_iteration
              << std::endl;
}

int main() {
    XeApp nano_benchmarks("xe_nano_benchmarks.spv");

    /*
     * These iteration fields are not used for function call rate test cases.
     */
    probe_config_t probe_setting;
    probe_setting.warm_up_iteration = 1000;
    probe_setting.measure_iteration = 9000;

    api_static_probe_init();
    header_print_iteration("xeFunctionSetArgumentValue: Buffer argument",
                           probe_setting);
    latency::parameter_buffer(&nano_benchmarks, probe_setting);
    hardware_counter::parameter_buffer(&nano_benchmarks, probe_setting);
    fuction_call_rate::parameter_buffer(&nano_benchmarks, probe_setting);

    std::cout << std::endl;

    header_print_iteration("xeFunctionSetArgumentValue: Immediate argument",
                           probe_setting);
    latency::parameter_integer(&nano_benchmarks, probe_setting);
    hardware_counter::parameter_integer(&nano_benchmarks, probe_setting);
    fuction_call_rate::parameter_integer(&nano_benchmarks, probe_setting);
    std::cout << std::endl;

    header_print_iteration("xeFunctionSetArgumentValue: Image argument",
                           probe_setting);
    latency::parameter_integer(&nano_benchmarks, probe_setting);
    hardware_counter::parameter_integer(&nano_benchmarks, probe_setting);
    fuction_call_rate::parameter_integer(&nano_benchmarks, probe_setting);
    std::cout << std::endl;

    probe_setting.warm_up_iteration = 142;
    probe_setting.measure_iteration = 567;
    header_print_iteration("xeCommandListAppendLaunchFunction:", probe_setting);
    latency::launch_function_no_parameter(&nano_benchmarks, probe_setting);
    hardware_counter::launch_function_no_parameter(&nano_benchmarks,
                                                   probe_setting);
    std::cout << std::endl;

    probe_setting.warm_up_iteration = 5;
    probe_setting.measure_iteration = 10;
    header_print_iteration("xeCommandQueueExecuteCommandLists:", probe_setting);
    latency::command_list_empty_execute(&nano_benchmarks, probe_setting);
    hardware_counter::command_list_empty_execute(&nano_benchmarks,
                                                 probe_setting);
    fuction_call_rate::command_list_empty_execute(&nano_benchmarks,
                                                  probe_setting);
    std::cout << std::endl;


    api_static_probe_cleanup();

    return 0;
}
