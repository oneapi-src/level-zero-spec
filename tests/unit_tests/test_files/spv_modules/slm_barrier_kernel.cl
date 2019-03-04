kernel void slmBarrierSum(const global float *a, const global float *b,
                         global float *c) {
    const int global_id = get_global_id(0);
    const int local_id = get_local_id(0);

    local float a_local[16];
    float sum = 0.0f;
  
    a_local[local_id] = a[local_id] + b[local_id];
		
    barrier(CLK_LOCAL_MEM_FENCE);

    for (int i = 0; i < get_local_size(0); ++i) {
      sum += a_local[i];
    }
    barrier(CLK_LOCAL_MEM_FENCE);

    c[global_id] = sum;
}