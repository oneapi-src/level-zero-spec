#pragma once
void matmat_host(int n, int m, int p, float *a, float *b, float *c);

int xeInit();
int xeInitProgram(const char *path = "mat_mult.spv",
                  const char *functionName = "matmat_gpu");
int xeUseCLProgram();
int xeInitBuffers();
int xeUseCLBuffers();
int xeUseCLCmdQueue();
int xeInitCmdQueue();
int xeMemCopyIn();
int xeCompute(const bool partial=false);
int xeMemCopyOut();
void xeCleanup();

int clInit();
int clInitProgram(const char *path = "mat_mult.cl",
                  const char *functionName = "matmat_gpu");
int clInitBuffers();
int clMemCopyIn();
int clCompute(const bool partial=false);
int clMemCopyOut();
void clCleanup();

void initArrays();
int validateArrays(float *c);
int validateResults(bool aubMode);

static inline int xeComputePartial() {
    return xeCompute(true);
}

static inline int clComputePartial() {
    return clCompute(true);
}

static inline int xeComputeAndCopy() {
    int ret;

    ret = xeMemCopyIn();
    if (ret)
        return -1;

    ret = xeCompute();
    if (ret)
        return -1;

    ret = xeMemCopyOut();
    if (ret)
        return -1;

    return 0;
}

static inline int clComputeAndCopy() {
    int ret;

    ret = clMemCopyIn();
    if (ret)
        return -1;

    ret = clCompute();
    if (ret)
        return -1;

    ret = clMemCopyOut();
    if (ret)
        return -1;

    return 0;
}
