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

/* Workaround until query of max memory size is fixed*/
#define MAX_DEVICE_OBJECT_SIZE 3315838976

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

enum TimingMeasurement {
    BANDWIDTH = 0,
    KERNEL_LAUNCH_LATENCY,
    KERNEL_COMPLETE_LATENCY
};

struct L0Context {
  xe_command_queue_handle_t command_queue;
  xe_command_list_handle_t command_list;
  xe_module_handle_t module;
  xe_mem_allocator_handle_t allocator;
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
  std::vector<uint8_t> load_binary_file(const std::string &file_path);
};

class XePeak
{
public:

  bool use_event_timer = false;
  bool verbose = false;
  bool run_global_bw = true;
  bool run_sp_compute = true;
  bool run_dp_compute = true;
  bool run_int_compute = true;
  bool run_transfer_bw = true;
  bool run_kernel_lat = true;
  int specified_platform, specified_device;
  uint32_t global_bw_max_size = 1 << 29;
  uint32_t iters = 50;

  int parse_arguments(int argc, char **argv);

  float run_kernel(L0Context context, xe_function_handle_t &function,
                 uint64_t total_number_work_items, int iters, TimingMeasurement type);
  void set_workgroups(L0Context &context,
        const uint64_t total_work_items_requested, uint32_t *group_size_x,
        uint32_t *group_size_y, uint32_t *group_size_z,
        xe_thread_group_dimensions_t *thread_group_dimensions);
  uint64_t convert_cl_to_xe_work_item_count(uint64_t global_work_size, uint64_t local_size);
  /* Benchmark Functions*/
  void peak_global_bw_setup_function(L0Context &context,
                                   xe_function_handle_t &function,
                                   const char *name, void *input, void *output);
  void xe_peak_global_bw(L0Context &context);
  void xe_peak_kernel_latency(L0Context &context);
};


#endif /* XE_PEAK_H */

