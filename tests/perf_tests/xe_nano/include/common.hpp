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
#ifndef _COMMON_HPP_
#define _COMMON_HPP_
#include <chrono>
#include <string>
#include <iostream>
#include <vector>

class TimerNanosecond {
  public:
    TimerNanosecond() {
        overhead();
    }
    inline void start() {
        time_start = std::chrono::high_resolution_clock::now();
    }

    inline void end() {
        time_end = std::chrono::high_resolution_clock::now();
    }

    inline int64_t period_minus_overhead() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start).count() - time_overhead;
    }

    inline bool has_it_been(long long int moment) {
	std::chrono::high_resolution_clock::time_point time_now =
                                     std::chrono::high_resolution_clock::now();
        auto period = std::chrono::duration_cast<std::chrono::nanoseconds>
							(time_now - time_start);
        return (period.count() >= moment);
    }

  private:
    std::chrono::high_resolution_clock::time_point time_start, time_end;
    int64_t time_overhead;

    inline void overhead() {
        start();
        end();
        auto period = std::chrono::duration_cast<std::chrono::nanoseconds>(time_end - time_start);
        time_overhead = period.count();
    }
};

extern bool verbose;

template <bool TerminateOnFailure, typename ResulT>
inline void validate(ResulT result, const char *message) {
    if (result != 0) { /* assumption 0 is success */
        std::cerr << (TerminateOnFailure ? "ERROR : " : "WARNING : ")
                  << message << " : " << result << std::endl;
        if (TerminateOnFailure) {
            std::terminate();
        }
        return;
    }

    if (verbose) {
        std::cerr << " SUCCESS : " << message << std::endl;
    }
}

#define SUCCESS_OR_TERMINATE(CALL) validate<true>(CALL, #CALL)

template <typename T>
int size_in_bytes(const std::vector<T> &v) {
    return static_cast<int>(sizeof(T) * v.size());
}

#define ERROR_RETURN(retval)                                   \
    {                                                          \
        std::cerr << "ERROR : " << __FILE__ << ":" << __LINE__ \
                  << " " << ret << std::endl;                  \
        std::terminate();                                      \
    }

#endif /* _COMMON_HPP_ */
