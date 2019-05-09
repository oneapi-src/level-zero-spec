#include "../xello_worlds.h"
#include "xello_interop_common.h"

int main(int argc, char **argv) {
    int ret;

    if (isParamEnabled(argc, argv, "-v", "--verbose"))
        verbose = true;

    initArrays();

    ret = clInit();
    if (ret)
        return -1;

    ret = clInitProgram();
    if (ret)
        return -1;

    ret = clInitBuffers();
    if (ret)
        return -1;

    ret = xeInit();
    if (ret)
        return -1;

    ret = xeInitProgram();
    if (ret)
        return -1;

    ret = xeInitBuffers();
    if (ret)
        return -1;

    ret = xeUseCLCmdQueue();
    if (ret)
        return -1;

    ret = clCompute();
    if (ret)
        return -1;

    ret = xeCompute();
    if (ret)
        return -1;

    ret = validateResults(isAubMode(argc, argv));
    if (ret)
        return -1;

    xeCleanup();
    clCleanup();

    return 0;
}
