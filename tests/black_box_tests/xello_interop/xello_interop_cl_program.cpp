#include "../xello_worlds.h"
#include "xello_interop_common.h"

int main(int argc, char **argv) {
    int ret;
    bool test_register_cl_program = true;

    initArrays();

    ret = xeInit();
    if (ret)
        return -1;

    ret = clInit();
    if (ret)
        return -1;

    if (test_register_cl_program) {
        ret = clInitProgram();
        if (ret)
            return -1;

        ret = xeUseCLProgram();
        if (ret)
            return -1;
    } else {
        ret = xeInitProgram();
        if (ret)
            return -1;

        ret = clInitProgram();
        if (ret)
            return -1;
    }

    ret = xeInitBuffers();
    if (ret)
        return -1;

    ret = clInitBuffers();
    if (ret)
        return -1;

    ret = clCompute();
    if (ret)
        return -1;

    ret = xeInitCmdQueue();
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

