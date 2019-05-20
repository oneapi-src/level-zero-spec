/*
 * Copyright (c) 2017,2019 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

R"===(

__kernel void CopyBufferToBufferSide(
    __global uchar* pDst,
    const __global uchar* pSrc,
    unsigned int len)
{
    unsigned int gid = get_global_id(0);
    if (gid < len) {
        pDst[ gid ] = pSrc[ gid ];
    }
}

__kernel void CopyBufferToBufferMiddle(
    __global uint* pDst,
    const __global uint* pSrc,
    unsigned int elems)
{
    unsigned int gid = get_global_id(0);
    if (gid < elems) {
        uint4 loaded = vload4(gid, pSrc);
        vstore4(loaded, gid, pDst);
    }
}

)==="
