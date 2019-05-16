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
#include <iomanip>
#include "benchmark.hpp"
#include "gtest/gtest.h"

using namespace xe_api_benchmarks;

namespace {
class XeNano : public ::testing::Test {
    protected:
        XeNano() {
            api_static_probe_init();
            benchmark = new XeApp("xe_nano_benchmarks.spv");
            probe_setting.warm_up_iteration = 0;
            probe_setting.measure_iteration = 0;
        }

        ~XeNano() override {
              api_static_probe_cleanup();
              delete benchmark;
        }

        void header_print_iteration(std::string prefix,
                                    probe_config_t &probe_setting) {
            std::cout << " All measurements are averaged per call except the function call rate metric"
                      << std::endl;
            std::cout << std::left << std::setw(25) << " " + prefix
                      << std::internal
                      << "Warm up iterations "
                      << probe_setting.warm_up_iteration
                      << std::setw(30) << " Measured iterations "
                      << probe_setting.measure_iteration
                      << std::endl;
        }

        XeApp *benchmark;
        probe_config_t probe_setting;
};

TEST_F(XeNano, xeFunctionSetArgumentValue_Buffer) {
    probe_setting.warm_up_iteration = 1000;
    probe_setting.measure_iteration = 9000;

    header_print_iteration("Buffer argument", probe_setting);
    latency::parameter_buffer(benchmark, probe_setting);
    hardware_counter::parameter_buffer(benchmark, probe_setting);
    fuction_call_rate::parameter_buffer(benchmark, probe_setting);
    std::cout << std::endl;
}

TEST_F(XeNano, xeFunctionSetArgumentValue_Immediate) {
    probe_setting.warm_up_iteration = 1000;
    probe_setting.measure_iteration = 9000;

    header_print_iteration("Immediate argument", probe_setting);
    latency::parameter_integer(benchmark, probe_setting);
    hardware_counter::parameter_integer(benchmark, probe_setting);
    fuction_call_rate::parameter_integer(benchmark, probe_setting);
    std::cout << std::endl;
}

TEST_F(XeNano, xeFunctionSetArgumentValue_Image) {
    probe_setting.warm_up_iteration = 1000;
    probe_setting.measure_iteration = 9000;

    header_print_iteration("Image argument", probe_setting);
    latency::parameter_integer(benchmark, probe_setting);
    hardware_counter::parameter_integer(benchmark, probe_setting);
    fuction_call_rate::parameter_integer(benchmark, probe_setting);
    std::cout << std::endl;
}

TEST_F(XeNano, xeCommandListAppendLaunchFunction) {
    probe_setting.warm_up_iteration = 142;
    probe_setting.measure_iteration = 567;

    header_print_iteration("", probe_setting);
    latency::launch_function_no_parameter(benchmark, probe_setting);
    hardware_counter::launch_function_no_parameter(benchmark, probe_setting);
    std::cout << std::endl;
}

TEST_F(XeNano, xeCommandQueueExecuteCommandLists) {
    probe_setting.warm_up_iteration = 5;
    probe_setting.measure_iteration = 10;
    header_print_iteration("", probe_setting);
    latency::command_list_empty_execute(benchmark, probe_setting);
    hardware_counter::command_list_empty_execute(benchmark, probe_setting);
    fuction_call_rate::command_list_empty_execute(benchmark, probe_setting);
    std::cout << std::endl;
}
} /* end namespace */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
