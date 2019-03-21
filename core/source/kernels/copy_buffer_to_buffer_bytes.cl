__kernel void copyBufferToBufferBytes(__global uchar *dst, const __global uchar *src) {
    unsigned int gid = get_global_id(0);
    dst[gid] = (uchar)(src[gid]);
}