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

/*
 * The test cases are generated using macros and #include's to facilitate
 * code resuse when creating nano probes.  Each test case is written once
 * and imported per nano probe such as the latency and hardware counter
 * probes.
 *
 * Each test case is written with the NANO_PROBE() macro around the
 * function call to be measured. When each test case is imported,
 * the NANO_PROBE() is redefined to a type of probe, so that the
 * test case is generated for that specific probe.
 *
 * When a test case is added, benchmark.hpp should be updated.
 */
#include "benchmark.hpp"
#include "api_static_probe.hpp"

namespace xe_api_benchmarks {
/*
 * For each test case created, the NANO_PROBE macro needs to be redefined to
 * generate code with the specific probe.
 */
#undef NANO_PROBE
#define NANO_PROBE PROBE_MEASURE_LATENCY_ITERATION
namespace latency {
#include "benchmark_template/set_parameter.cpp"
#include "benchmark_template/command_list.cpp"
} /* namespace latency */

#undef NANO_PROBE
#define NANO_PROBE PROBE_MEASURE_HARDWARE_COUNTERS
namespace hardware_counter {
#include "benchmark_template/set_parameter.cpp"
#include "benchmark_template/command_list.cpp"
} /* namespace hardware_counter */

#undef NANO_PROBE
#define NANO_PROBE PROBE_MEASURE_FUNCTION_CALL_RATE
namespace fuction_call_rate {
#include "benchmark_template/set_parameter.cpp"
#include "benchmark_template/command_list.cpp"
} /* namespace fuction_call_rate */
} /* namespace xe_api_benchmarks */
