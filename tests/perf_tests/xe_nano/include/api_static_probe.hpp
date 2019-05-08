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
#include "common.hpp"

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

#define PROBE_MEASURE_LATENCY_ITERATION(prefix, iteration_number, function_name, ...) \
    _function_call_iter_measure_latency(__FILE__, __LINE__, #function_name,           \
                                        prefix, iteration_number,                     \
                                        function_name,                                \
                                        __VA_ARGS__)
template <typename... Params, typename... Args>
int64_t _function_call_iter_measure_latency(const std::string filename,
                                            const int line_number,
                                            const std::string function_name,
                                            const std::string prefix,
                                            const int iteration_number,
                                            xe_result_t (*api_function)(Params... params),
                                            Args... args) {
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
#endif /* _API_STATIC_PROBE_HPP_ */
