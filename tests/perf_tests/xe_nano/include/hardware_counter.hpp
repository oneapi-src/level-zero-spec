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
#ifndef _HARDWARE_COUNTER_HPP_
#define _HARDWARE_COUNTER_HPP_
#include <iostream>

class HardwareCounter {
  public:
    HardwareCounter();
    ~HardwareCounter();
    void start(void);
    void end(void);
    long long counter_instructions(void);
    long long counter_cycles(void);
    bool is_supported(void);
    static std::string support_warning(void);

  private:
    bool _counter_enabled;
    int event_set;

    /*
     * It is used to check that at least on measurement was taken
     * by calling start() and end()
     */
    bool measurement_taken;

    /*
     * It is used to determine if user finished the measurement
     * by calling end() after start().
     */
    bool active_period;

    static const unsigned int number_events = 2;
    long long values[number_events];
    inline void counter_asserts(void);
};

#endif /* _HARDWARE_COUNTER_HPP_ */
