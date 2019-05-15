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
#include "hardware_counter.hpp"
#include <assert.h>

HardwareCounter::HardwareCounter() {
}

HardwareCounter::~HardwareCounter() {
}

void HardwareCounter::start(void) {
    assert(0);
}

void HardwareCounter::end(void) {
    assert(0);
}

void HardwareCounter::counter_asserts(void) {
    assert(0);
}

long long HardwareCounter::counter_instructions(void) {
    assert(0);
    return -1;
}

long long HardwareCounter::counter_cycles(void) {
    assert(0);
    return -1;
}

bool HardwareCounter::is_supported(void) {
    return false;
}

std::string HardwareCounter::support_warning(void) {
    return "Hardware counters are not supported. Compile benchmark with the PAPI library on Unix system";
}
