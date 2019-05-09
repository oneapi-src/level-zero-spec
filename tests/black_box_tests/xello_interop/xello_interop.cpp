
#include "xello_interop_common.h"
#include "../xello_worlds.h"

/*
 * Enables testing of interop features in combination with each other.
 * (Interop features must be explicitly enabled.)
 */

int main(int argc, char **argv) {
    int ret;
    bool do_register_cl_program = isParamEnabled(argc, argv, "-p", "--program");
    bool do_register_cl_cmd_queue = isParamEnabled(argc, argv, "-q", "--cmd-queue");
    bool do_register_cl_memory = isParamEnabled(argc, argv, "-m", "--memory");

    if (isParamEnabled(argc, argv, "-h", "--help")) {
        std::cout << "usage: " << argv[0]
                  << " [-p | --program] [-q | --cmd-queue] [-m | --memory]\n"
                  << " tests XE-OpenCL interop by performing matrix multiply "
                  << "on XE and OpenCL while optionally sharing CL programs, "
                  << "command queues, and memory buffers\n";
        return 0;
    }

    if (isParamEnabled(argc, argv, "-v", "--verbose"))
        verbose = true;

    initArrays();

    ret = xeInit();
    if (ret)
        return -1;

    ret = clInit();
    if (ret)
        return -1;

    if (do_register_cl_program) {
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

    if (do_register_cl_memory) {
        ret = clInitBuffers();
        if (ret)
            return -1;

        ret = xeUseCLBuffers();
        if (ret)
            return -1;
    } else {
        ret = xeInitBuffers();
        if (ret)
            return -1;

        ret = clInitBuffers();
        if (ret)
            return -1;
    }

    ret = clCompute();
    if (ret)
        return -1;

    if (do_register_cl_cmd_queue) {
        ret = xeUseCLCmdQueue();
        if (ret)
            return -1;
    } else {
        ret = xeInitCmdQueue();
        if (ret)
            return -1;
    }

    ret = xeCompute();
    if (ret)
        return -1;

    ret = validateResults(isAubMode(argc, argv));
    if (ret)
        return -1;

    xeCleanup();
    clCleanup();

    return ret;
}
