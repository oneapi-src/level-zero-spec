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

#undef FETCH_2
#undef FETCH_8

#define FETCH_2(sum, id, A, jumpBy)      sum += A[id];   id += jumpBy;   sum += A[id];   id += jumpBy;
#define FETCH_4(sum, id, A, jumpBy)      FETCH_2(sum, id, A, jumpBy);   FETCH_2(sum, id, A, jumpBy);
#define FETCH_8(sum, id, A, jumpBy)      FETCH_4(sum, id, A, jumpBy);   FETCH_4(sum, id, A, jumpBy);

#define FETCH_PER_WI  16

// Kernels fetching by local_size offset
__kernel void global_bandwidth_v1_local_offset(__global float *A, __global float *B)
{
    int id = (get_group_id(0) * get_local_size(0) * FETCH_PER_WI) + get_local_id(0);
    float sum = 0;

    FETCH_8(sum, id, A, get_local_size(0));
    FETCH_8(sum, id, A, get_local_size(0));

    B[get_global_id(0)] = sum;
}


__kernel void global_bandwidth_v2_local_offset(__global float2 *A, __global float *B)
{
    int id = (get_group_id(0) * get_local_size(0) * FETCH_PER_WI) + get_local_id(0);
    float2 sum = 0;

    FETCH_8(sum, id, A, get_local_size(0));
    FETCH_8(sum, id, A, get_local_size(0));

    B[get_global_id(0)] = (sum.S0) + (sum.S1);
}


__kernel void global_bandwidth_v4_local_offset(__global float4 *A, __global float *B)
{
    int id = (get_group_id(0) * get_local_size(0) * FETCH_PER_WI) + get_local_id(0);
    float4 sum = 0;

    FETCH_8(sum, id, A, get_local_size(0));
    FETCH_8(sum, id, A, get_local_size(0));

    B[get_global_id(0)] = (sum.S0) + (sum.S1) + (sum.S2) + (sum.S3);
}


__kernel void global_bandwidth_v8_local_offset(__global float8 *A, __global float *B)
{
    int id = (get_group_id(0) * get_local_size(0) * FETCH_PER_WI) + get_local_id(0);
    float8 sum = 0;

    FETCH_8(sum, id, A, get_local_size(0));
    FETCH_8(sum, id, A, get_local_size(0));

    B[get_global_id(0)] = (sum.S0) + (sum.S1) + (sum.S2) + (sum.S3) + (sum.S4) + (sum.S5) + (sum.S6) + (sum.S7);
}

__kernel void global_bandwidth_v16_local_offset(__global float16 *A, __global float *B)
{
    int id = (get_group_id(0) * get_local_size(0) * FETCH_PER_WI) + get_local_id(0);
    float16 sum = 0;

    FETCH_8(sum, id, A, get_local_size(0));
    FETCH_8(sum, id, A, get_local_size(0));

    float t = (sum.S0) + (sum.S1) + (sum.S2) + (sum.S3) + (sum.S4) + (sum.S5) + (sum.S6) + (sum.S7);
    t += (sum.S8) + (sum.S9) + (sum.SA) + (sum.SB) + (sum.SC) + (sum.SD) + (sum.SE) + (sum.SF);
    B[get_global_id(0)] = t;
}


// Kernels fetching by global_size offset
__kernel void global_bandwidth_v1_global_offset(__global float *A, __global float *B)
{
    int id = get_global_id(0);
    float sum = 0;

    FETCH_8(sum, id, A, get_global_size(0));
    FETCH_8(sum, id, A, get_global_size(0));

    B[get_global_id(0)] = sum;
}


__kernel void global_bandwidth_v2_global_offset(__global float2 *A, __global float *B)
{
    int id = get_global_id(0);
    float2 sum = 0;

    FETCH_8(sum, id, A, get_global_size(0));
    FETCH_8(sum, id, A, get_global_size(0));

    B[get_global_id(0)] = (sum.S0) + (sum.S1);
}


__kernel void global_bandwidth_v4_global_offset(__global float4 *A, __global float *B)
{
    int id = get_global_id(0);
    float4 sum = 0;

    FETCH_8(sum, id, A, get_global_size(0));
    FETCH_8(sum, id, A, get_global_size(0));

    B[get_global_id(0)] = (sum.S0) + (sum.S1) + (sum.S2) + (sum.S3);
}


__kernel void global_bandwidth_v8_global_offset(__global float8 *A, __global float *B)
{
    int id = get_global_id(0);
    float8 sum = 0;

    FETCH_8(sum, id, A, get_global_size(0));
    FETCH_8(sum, id, A, get_global_size(0));

    B[get_global_id(0)] = (sum.S0) + (sum.S1) + (sum.S2) + (sum.S3) + (sum.S4) + (sum.S5) + (sum.S6) + (sum.S7);
}

__kernel void global_bandwidth_v16_global_offset(__global float16 *A, __global float *B)
{
    int id = get_global_id(0);
    float16 sum = 0;

    FETCH_8(sum, id, A, get_global_size(0));
    FETCH_8(sum, id, A, get_global_size(0));

    float t = (sum.S0) + (sum.S1) + (sum.S2) + (sum.S3) + (sum.S4) + (sum.S5) + (sum.S6) + (sum.S7);
    t += (sum.S8) + (sum.S9) + (sum.SA) + (sum.SB) + (sum.SC) + (sum.SD) + (sum.SE) + (sum.SF);
    B[get_global_id(0)] = t;
}

