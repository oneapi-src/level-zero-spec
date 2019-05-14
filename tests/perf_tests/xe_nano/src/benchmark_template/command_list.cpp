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

void launch_function_no_parameter(XeApp *benchmark,
				  probe_config_t &probe_setting) {
    xe_function_handle_t function;
    xe_command_list_handle_t command_list;
    benchmark->commandListCreate(&command_list);

    benchmark->functionCreate(&function, "function_no_parameter");

    xe_thread_group_dimensions_t thread_group_dimensions;
    thread_group_dimensions.groupCountX = 1;
    thread_group_dimensions.groupCountY = 1;
    thread_group_dimensions.groupCountZ = 1;

    /* Warm up */
    for (int i = 0; i < probe_setting.warm_up_iteration; i++) {
	xeCommandListAppendLaunchFunction(command_list, function,
					  &thread_group_dimensions,
					  nullptr, 0, nullptr);
    }

    NANO_PROBE(" Function with no parameters\t", probe_setting,
	       xeCommandListAppendLaunchFunction, command_list, function,
	       &thread_group_dimensions, nullptr, 0, nullptr);

    benchmark->functionDestroy(function);
    benchmark->commandListDestroy(command_list);
}

void command_list_empty_execute(XeApp *benchmark,
                                probe_config_t &probe_setting) {
    xe_command_list_handle_t command_list;

    benchmark->commandListCreate(&command_list);
    benchmark->commandListClose(command_list);

    /* Warm up */
    for (int i = 0; i < probe_setting.warm_up_iteration; i++) {
	xeCommandQueueExecuteCommandLists(benchmark->command_queue, 1,
					  &command_list, nullptr);
    }

    NANO_PROBE(" Empty command list\t", probe_setting,
	       xeCommandQueueExecuteCommandLists, benchmark->command_queue, 1,
	       &command_list, nullptr);

    benchmark->commandListDestroy(command_list);
}
