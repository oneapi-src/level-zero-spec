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
#include <locale>
#include <assert.h>
#include <iomanip>
#include "xe_api.h"
#include "common.hpp"
#include "hardware_counter.hpp"

const std::string PREFIX_LATENCY = "[ PERF LATENCY nS ]\t";
const std::string PREFIX_FUNCTION_CALL_RATE = "[ PERF FUNC_CALL_RATE ]\t";
const std::string PREFIX_CYCLES = "[ PERF CYCLES ]\t\t";
const std::string PREFIX_INSTRUCTION = "[ PERF INSTRUCTIONS ]\t";
const std::string PREFIX_CPI = "[ PERF CPI ]\t\t";

const std::string UNIT_LATENCY = "nanoseconds";
const std::string UNIT_FUNCTION_CALL_RATE = "function calls/sec";
const std::string UNIT_CYCLES = "cycles";
const std::string UNIT_INSTRUCTION = "instructions";
const std::string UNIT_CPI = UNIT_CYCLES + "/" + UNIT_INSTRUCTION;

extern HardwareCounter *hardware_counters;
void api_static_probe_init();
void api_static_probe_cleanup();
bool api_static_probe_is_init();

typedef struct _probe_cofig {
    int warm_up_iteration;
    int measure_iteration;
} probe_config_t;

template <typename T>
inline void print_probe_output(const std::string prefix,
                               const std::string filename,
                               const int line_number,
                               const std::string function_name,
                               T output_value, const std::string suffix) {
    std::cout.imbue(std::locale(""));
    std::cout << prefix
              << (verbose ? filename + ":" + std::to_string(line_number) + "\t" : "")
              << (verbose ? function_name + "\t" : "")
              << std::setw(15) << std::setprecision(5) << output_value
              << "\t" + suffix
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

    print_probe_output(PREFIX_LATENCY + prefix, filename, line_number,
                       function_name, int_nsec / iteration_number,
                       UNIT_LATENCY);

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

    if (hardware_counters->is_supported() == false) {
        std::string warning = HardwareCounter::support_warning();
        print_probe_output(UNIT_CYCLES + prefix, filename, line_number,
                           function_name, warning, "");
        /*
         * Even though no hardware counters are retrieved, call the api
         * function once in case other parts of the test case expect the
         * api function to update some state.
         */
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

    print_probe_output(PREFIX_INSTRUCTION + prefix, filename, line_number,
                       function_name, normalized_instruction_count,
                       UNIT_INSTRUCTION);
    print_probe_output(PREFIX_CYCLES + prefix, filename, line_number,
                       function_name, normalized_cycle_count,
                       UNIT_CYCLES);
    print_probe_output(PREFIX_CPI + prefix, filename, line_number, function_name,
                       cycle_per_instruction, UNIT_CPI);
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
    print_probe_output(PREFIX_FUNCTION_CALL_RATE + prefix, filename,
                       line_number, function_name, function_call_counter,
                       UNIT_FUNCTION_CALL_RATE);
}
#endif /* _API_STATIC_PROBE_HPP_ */
