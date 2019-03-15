kernel void test_printf(__global char *buffer1, const __global char *buffer2) {
    const int global_id = get_global_id(0);
    const int local_id = get_local_id(0);

    printf("local_id = %d, global_id = %d\n", local_id, global_id);
}