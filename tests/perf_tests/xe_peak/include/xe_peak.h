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

#ifndef XE_PEAK_H
#define XE_PEAK_H

#include "../include/common.h"

/* xe includes */
#include "xe_barrier.h"
#include "xe_cmdqueue.h"
#include "xe_cmdlist.h"
#include "xe_copy.h"
#include "xe_driver.h"
#include "xe_device.h"
#include "xe_memory.h"
#include "xe_module.h"
#include "xe_event.h"

#define MIN(X, Y) (X < Y) ? X : Y

#undef FETCH_2
#undef FETCH_8

#define FETCH_2(sum, id, A, jumpBy)                                            \
  sum += A[id];                                                                \
  id += jumpBy;                                                                \
  sum += A[id];                                                                \
  id += jumpBy;
#define FETCH_4(sum, id, A, jumpBy)                                            \
  FETCH_2(sum, id, A, jumpBy);                                                 \
  FETCH_2(sum, id, A, jumpBy);
#define FETCH_8(sum, id, A, jumpBy)                                            \
  FETCH_4(sum, id, A, jumpBy);                                                 \
  FETCH_4(sum, id, A, jumpBy);

#define FETCH_PER_WI 16

enum class TimingMeasurement {
    BANDWIDTH = 0,
    BANDWIDTH_EVENT_TIMING,
    KERNEL_LAUNCH_LATENCY,
    KERNEL_COMPLETE_LATENCY
};

struct L0Context {
  xe_command_queue_handle_t command_queue;
  xe_command_list_handle_t command_list;
  xe_module_handle_t module;
  xe_device_handle_t device;
  uint32_t device_count = 0;
  const uint32_t default_device = 0;
  const uint32_t command_queue_id = 0;
  xe_device_properties_t device_property;
  xe_device_compute_properties_t device_compute_property;
  bool verbose = false;

  void init_xe();
  void clean_xe();
  void print_xe_device_properties(const xe_device_properties_t &props);
  void reset_commandlist();
  void execute_commandlist_and_sync();
  std::vector<uint8_t> load_binary_file(const std::string &file_path);
  void create_module(std::vector<uint8_t> binary_file);
};

struct XeWorkGroups {
    xe_thread_group_dimensions_t thread_group_dimensions;
    uint32_t group_size_x;
    uint32_t group_size_y;
    uint32_t group_size_z;
};

class XePeak
{
public:

  bool use_event_timer = false;
  bool verbose = false;
  bool run_global_bw = true;
  bool run_hp_compute = true;
  bool run_sp_compute = true;
  bool run_dp_compute = true;
  bool run_int_compute = true;
  bool run_transfer_bw = true;
  bool run_kernel_lat = true;
  int specified_platform, specified_device;
  uint32_t global_bw_max_size = 1 << 29;
  uint32_t transfer_bw_max_size = 1 << 29;
  uint32_t iters = 50;
  uint32_t warmup_iterations = 10;

  int parse_arguments(int argc, char **argv);

  /* Helper Functions */
  float run_kernel(L0Context context, xe_function_handle_t &function,
                 struct XeWorkGroups &workgroup_info, TimingMeasurement type, bool reset_command_list=true);
  uint64_t set_workgroups(L0Context &context,
        const uint64_t total_work_items_requested, struct XeWorkGroups *workgroup_info);
  uint64_t convert_cl_to_xe_work_item_count(uint64_t global_work_size, uint64_t local_size);
  void setup_function(L0Context &context,
                                   xe_function_handle_t &function,
                                   const char *name, void *input, void *output);
  uint64_t get_max_work_items(L0Context &context);
  void print_test_complete();
  void run_command_queue(L0Context &context);
  /* Benchmark Functions*/
  void xe_peak_global_bw(L0Context &context);
  void xe_peak_kernel_latency(L0Context &context);
  void xe_peak_hp_compute(L0Context &context);
  void xe_peak_sp_compute(L0Context &context);
  void xe_peak_dp_compute(L0Context &context);
  void xe_peak_int_compute(L0Context &context);
  void xe_peak_transfer_bw(L0Context &context);

private:

void _transfer_bw_gpu_copy(L0Context &context, void *destination_buffer,
                           void *source_buffer, size_t buffer_size);
void _transfer_bw_host_copy(void *destination_buffer, void *source_buffer,
                            size_t buffer_size);
void _transfer_bw_shared_memory(L0Context &context,
                                std::vector<float> local_memory);
TimingMeasurement is_bandwidth_with_event_timer(void);
};

uint64_t max_device_object_size(L0Context &context);
TimingMeasurement is_bandwidth_with_event_timer(void);

#endif /* XE_PEAK_H */