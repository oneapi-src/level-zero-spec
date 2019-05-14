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

int main() {
    XeApp nano_benchmarks("xe_nano_benchmarks.spv");
    int warm_up_iteration = 1000;
    int measure_iteration = 9000;

    api_static_probe_init();
    std::cout << "xeFunctionSetArgumentValue: Buffer argument"
              << "\tWarm up iterations " << warm_up_iteration
              << "\tMeasured iterations " << measure_iteration
              << std::endl;
    latency::parameter_buffer(&nano_benchmarks, warm_up_iteration,
                              measure_iteration);
    hardware_counter::parameter_buffer(&nano_benchmarks, warm_up_iteration,
                                       measure_iteration);
    fuction_call_rate::parameter_buffer(&nano_benchmarks, warm_up_iteration,
                                        measure_iteration);

    std::cout << std::endl;

    std::cout << "xeFunctionSetArgumentValue: Immediate argument"
              << "\tWarm up iterations " << warm_up_iteration
              << "\tMeasured iterations " << measure_iteration
              << std::endl;
    latency::parameter_integer(&nano_benchmarks, warm_up_iteration,
                               measure_iteration);
    hardware_counter::parameter_integer(&nano_benchmarks, warm_up_iteration,
                                        measure_iteration);
    fuction_call_rate::parameter_integer(&nano_benchmarks, warm_up_iteration,
                                         measure_iteration);
    std::cout << std::endl;

    std::cout << "xeFunctionSetArgumentValue: Image argument"
              << "\tWarm up iterations " << warm_up_iteration
              << "\tMeasured iterations " << measure_iteration
              << std::endl;
    latency::parameter_integer(&nano_benchmarks, warm_up_iteration,
                               measure_iteration);
    hardware_counter::parameter_integer(&nano_benchmarks, warm_up_iteration,
                                        measure_iteration);
    fuction_call_rate::parameter_integer(&nano_benchmarks, warm_up_iteration,
                                         measure_iteration);
    std::cout << std::endl;

    warm_up_iteration = 142;
    measure_iteration = 567;
    std::cout << "xeCommandListAppendLaunchFunction:"
              << "\tWarm up iterations " << warm_up_iteration
              << "\tMeasured iterations " << measure_iteration
              << std::endl;
    latency::launch_function_no_parameter(&nano_benchmarks, warm_up_iteration,
                                          measure_iteration);
    hardware_counter::launch_function_no_parameter(&nano_benchmarks,
                                                   warm_up_iteration,
                                                   measure_iteration);
    std::cout << std::endl;

    warm_up_iteration = 5;
    measure_iteration = 10;
    std::cout << "xeCommandQueueExecuteCommandLists:"
              << "\tWarm up iterations " << warm_up_iteration
              << "\tMeasured iterations " << measure_iteration
              << std::endl;
    latency::command_list_empty_execute(&nano_benchmarks, warm_up_iteration,
                                        measure_iteration);
    hardware_counter::command_list_empty_execute(&nano_benchmarks,
                                                 warm_up_iteration,
                                                 measure_iteration);
    fuction_call_rate::command_list_empty_execute(&nano_benchmarks,
                                                  warm_up_iteration,
                                                  measure_iteration);
    std::cout << std::endl;


    api_static_probe_cleanup();

    return 0;
}
