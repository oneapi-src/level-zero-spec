/*
 * Copyright(c) 2019 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining input_a copy
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
 * If function signatures are updated, benchmark_template/set_parameter.hpp needs to
 * be updated.
 */
void parameter_buffer(XeApp *benchmark, probe_config_t &probe_setting) {
    xe_function_handle_t function;
    void *input_buffer = nullptr;
    const std::vector<int8_t> input = {72, 101, 108, 108, 111, 32, 87, 111,
				       114, 108, 100, 33};
    benchmark->memoryAlloc(size_in_bytes(input), &input_buffer);

    benchmark->functionCreate(&function, "function_parameter_buffers");

    /* Warm up */
    for (int i = 0; i < probe_setting.warm_up_iteration; i++) {
        SUCCESS_OR_TERMINATE(
            xeFunctionSetArgumentValue(function, 0, sizeof(input_buffer),
				       &input_buffer));
        SUCCESS_OR_TERMINATE(
            xeFunctionSetArgumentValue(function, 1, sizeof(input_buffer),
				       &input_buffer));
        SUCCESS_OR_TERMINATE(
            xeFunctionSetArgumentValue(function, 2, sizeof(input_buffer),
				       &input_buffer));
        SUCCESS_OR_TERMINATE(
            xeFunctionSetArgumentValue(function, 3, sizeof(input_buffer),
				       &input_buffer));
        SUCCESS_OR_TERMINATE(
            xeFunctionSetArgumentValue(function, 4, sizeof(input_buffer),
				       &input_buffer));
        SUCCESS_OR_TERMINATE(
            xeFunctionSetArgumentValue(function, 5, sizeof(input_buffer),
				       &input_buffer));
    }

    NANO_PROBE(" Argument index 0\t", probe_setting,
               xeFunctionSetArgumentValue,
               function, 0, sizeof(input_buffer),
               &input_buffer);

    NANO_PROBE(" Argument index 5\t", probe_setting,
               xeFunctionSetArgumentValue,
               function, 5, sizeof(input_buffer),
               &input_buffer);

    benchmark->functionDestroy(function);
    benchmark->memoryFree(input_buffer);
}

void parameter_integer(XeApp *benchmark, probe_config_t &probe_setting) {
    xe_function_handle_t function;
    int input_a = 1;

    benchmark->functionCreate(&function, "function_parameter_integer");

    /* Warm up */
    for (int i = 0; i < probe_setting.warm_up_iteration; i++) {
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 0, sizeof(input_a), &input_a));
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 1, sizeof(input_a), &input_a));
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 2, sizeof(input_a), &input_a));
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 3, sizeof(input_a), &input_a));
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 4, sizeof(input_a), &input_a));
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 5, sizeof(input_a), &input_a));
    }

    NANO_PROBE(" Argument index 0\t", probe_setting,
               xeFunctionSetArgumentValue,
               function, 0, sizeof(input_a), &input_a);

    NANO_PROBE(" Argument index 5\t", probe_setting,
               xeFunctionSetArgumentValue,
               function, 5, sizeof(input_a), &input_a);

    benchmark->functionDestroy(function);
}

void parameter_image(XeApp *benchmark, probe_config_t &probe_setting) {
    xe_function_handle_t function;
    xe_image_handle_t input_a;

    benchmark->functionCreate(&function, "function_parameter_integer");

    /* Warm up */
    for (int i = 0; i < probe_setting.warm_up_iteration; i++) {
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 0, sizeof(input_a), &input_a));
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 1, sizeof(input_a), &input_a));
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 2, sizeof(input_a), &input_a));
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 3, sizeof(input_a), &input_a));
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 4, sizeof(input_a), &input_a));
        SUCCESS_OR_TERMINATE(
	    xeFunctionSetArgumentValue(function, 5, sizeof(input_a), &input_a));
    }

    NANO_PROBE(" Argument index 0\t", probe_setting,
               xeFunctionSetArgumentValue,
               function, 0, sizeof(input_a), &input_a);

    NANO_PROBE(" Argument index 5\t", probe_setting,
               xeFunctionSetArgumentValue,
               function, 5, sizeof(input_a), &input_a);

    benchmark->functionDestroy(function);
}
