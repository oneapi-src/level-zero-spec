#include "../xello_worlds.h"
#include "xello_interop_common.h"

int main(int argc, char **argv) {
    int ret;

    if (isParamEnabled(argc, argv, "-v", "--verbose"))
        verbose = true;

    initArrays();

    ret = xeInit();
    if (ret)
        return -1;

    ret = xeInitProgram("mat_mult_partial.spv", "matmat_partial_gpu");
    //ret = xeInitProgram();
    if (ret)
        return -1;

    ret = xeInitCmdQueue();
    if (ret)
        return -1;

    ret = clInit();
    if (ret)
        return -1;

    ret = clInitProgram("mat_mult_partial.cl", "matmat_partial_gpu");
    //ret = clInitProgram();
    if (ret)
        return -1;

    ret = clInitBuffers();
    if (ret)
        return -1;

    ret = xeUseCLBuffers();
    if (ret)
        return -1;

    /* can be done by CL or XE */
    ret = xeMemCopyIn();
    if (ret)
	return -1;

    ret = xeComputePartial();
    if (ret)
        return -1;

    ret = clComputePartial();
    if (ret)
        return -1;

    ret = clMemCopyOut();
    if (ret)
        return -1;

    ret = xeMemCopyOut();
    if (ret)
        return -1;

    ret = validateResults(isAubMode(argc, argv));
    if (ret)
        return -1;

    xeCleanup();
    clCleanup();

    return 0;
}
