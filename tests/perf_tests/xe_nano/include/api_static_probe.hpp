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
#ifndef _API_STATIC_PROBE_HPP_
#define _API_STATIC_PROBE_HPP_

#include <string>
#include <assert.h>
#include "xe_api.h"
#include "common.hpp"
#include "hardware_counter.hpp"

extern HardwareCounter *hardware_counters;
void api_static_probe_init();
void api_static_probe_cleanup();
bool api_static_probe_is_init();

typedef struct _probe_cofig {
    int warm_up_iteration;
    int measure_iteration;
    int duration_factor;
} probe_config_t;

template <typename T>
inline void print_probe_output(const std::string prefix,
                               const std::string filename,
                               const int line_number,
                               const std::string function_name,
                               T output_value, const std::string suffix) {
    std::cout << prefix
              << (verbose ? filename + ":" + std::to_string(line_number) + "\t" : "")
              << function_name
              << "\t"
              << output_value
              << suffix
              << std::endl;
}

#define PROBE_MEASURE_LATENCY_ITERATION(prefix, probe_setting, function_name, ...) \
    _function_call_iter_measure_latency(__FILE__, __LINE__, #function_name,        \
                                        prefix, probe_setting,                     \
                                        function_name,                             \
                                        __VA_ARGS__)
template <typename... Params, typename... Args>
int64_t _function_call_iter_measure_latency(const std::string filename,
                                            const int line_number,
                                            const std::string function_name,
                                            const std::string prefix,
                                            const probe_config_t &probe_setting,
                                            xe_result_t (*api_function)(Params... params),
                                            Args... args) {
    int iteration_number = probe_setting.measure_iteration;
    TimerNanosecond timer;

    timer.start();
    for (int i = 0; i < iteration_number; i++) {
        api_function(args...);
    }
    timer.end();

    auto int_nsec = timer.period_minus_overhead();

    print_probe_output(prefix, filename, line_number, function_name,
                       int_nsec / iteration_number, "\tnanoseconds");

    return int_nsec;
}

#define PROBE_MEASURE_HARDWARE_COUNTERS(prefix, probe_setting,      \
                                        function_name, ...)         \
    _function_call_iter_hardware_counters(__FILE__, __LINE__,       \
                                          #function_name,           \
                                          prefix, probe_setting,    \
                                          function_name,            \
                                          __VA_ARGS__)
template <typename... Params, typename... Args>
void _function_call_iter_hardware_counters(const std::string filename,
                                           const int line_number,
                                           const std::string function_name,
                                           const std::string prefix,
                                           const probe_config_t &probe_setting,
                                           xe_result_t (*api_function)(Params... params),
                                           Args... args) {
    int iteration_number = probe_setting.measure_iteration;

    assert(api_static_probe_is_init());
    if (HardwareCounter::is_supported() == false) {
        print_probe_output(prefix, filename, line_number, function_name,
                           "Hardware counters are not supported. Compile benchmark with the PAPI library on Unix system",
                           "");
        api_function(args...);
        return;
    }

    hardware_counters->start();
    for (int i = 0; i < iteration_number; i++) {
        api_function(args...);
    }
    hardware_counters->end();

    auto total_instruction_count = hardware_counters->counter_instructions();
    auto total_cycle_count = hardware_counters->counter_cycles();

    auto normalized_instruction_count =
        total_instruction_count / iteration_number;
    auto normalized_cycle_count = total_cycle_count / iteration_number;
    auto cycle_per_instruction =
        normalized_cycle_count / static_cast<double>(normalized_instruction_count);

    print_probe_output(prefix, filename, line_number, function_name,
                       normalized_instruction_count, "\tinstructions");
    print_probe_output(prefix, filename, line_number, function_name,
                       normalized_cycle_count, "\tcycles");
    print_probe_output(prefix, filename, line_number, function_name,
                       cycle_per_instruction, "\tcycles/instructions");
}

#define PROBE_MEASURE_FUNCTION_CALL_RATE(prefix, probe_setting, \
                                         function_name, ...)    \
    _function_call_rate_iter(__FILE__, __LINE__,                \
                             #function_name,                    \
                             prefix,                            \
                             function_name,                     \
                             __VA_ARGS__)
template <typename... Params, typename... Args>
void _function_call_rate_iter(const std::string filename,
                              const int line_number,
                              const std::string function_name,
                              const std::string prefix,
                              xe_result_t (*api_function)(Params... params),
                              Args... args) {
    TimerNanosecond timer;
    const int one_second_in_nano = 1000000000;
    /*
     * 500 ms will be used to count function calls. This is determined by
     * dividing 1 nanoseocnd by division_factor.
     */
    const int division_factor = 2;
    const int period = one_second_in_nano / division_factor;
    int function_call_counter = 0;

    /* Determine number of function calls per 250 milliseocnds */
    while (timer.has_it_been(period) == false) {
        api_function(args...);
	function_call_counter++;
    }

    timer.start();
    for (int i = 0; i < function_call_counter; i++) {
	    api_function(args...);
    }
    timer.end();

    auto int_nsec = timer.period_minus_overhead();
    function_call_counter = static_cast<int>(
				division_factor *
				(period / static_cast<long double>(int_nsec)) *
				function_call_counter);
    if (verbose) {
	/* It helps verify that function calls are one second */
        timer.start();
        for (int i = 0; i < function_call_counter; i++) {
                api_function(args...);
        }
        timer.end();

        int_nsec = timer.period_minus_overhead();
        std::cout << "Period " << int_nsec
		  << " number function calls " << function_call_counter
		  << std::endl;
    }
    print_probe_output(prefix, filename, line_number, function_name,
		       function_call_counter, "\tfunction calls");
}
#endif /* _API_STATIC_PROBE_HPP_ */
