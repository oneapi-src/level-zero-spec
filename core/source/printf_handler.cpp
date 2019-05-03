#include "printf_handler.h"
#include "device.h"
#include "graphics_allocation.h"
#include "memory_manager.h"

#include "runtime/kernel/kernel.h"
#include "runtime/program/print_formatter.h"

namespace L0 {

// TODO : Refactor in NEO to not need such heavy objects on the interface
struct DummyDevice : NEO::Device {
    DummyDevice() : NEO::Device(hwInfo, nullptr, 0) {
    }
    NEO::HardwareInfo hwInfo;
};

struct DummyKernel : NEO::Kernel {
    DummyKernel(NEO::Program *prog, NEO::KernelInfo &kernelInfo, NEO::Device *device)
        : NEO::Kernel(prog, kernelInfo, *device, false) {
    }
    NEO::KernelInfo dummyKernelInfo;
};

GraphicsAllocation *PrintfHandler::createPrintfBuffer(Device *device) {
    auto allocation = globalMemoryManager->allocateManagedMemory(device, PrintfHandler::printfBufferSize, MemoryConstants::pageSize64k);
    *reinterpret_cast<uint32_t *>(allocation->getHostAddress()) = PrintfHandler::printfSurfaceInitialDataSize;
    return allocation;
}

void PrintfHandler::printOutput(PtrRef<FunctionImmutableData> function, PtrRef<GraphicsAllocation> printfBuffer, Device *device) {
    auto *execEnv = static_cast<NEO::ExecutionEnvironment *>(device->getExecEnvironment());
    execEnv->getHardwareInfo();
    NEO::Program dummyProgram{*execEnv, nullptr, false};
    NEO::Device *deviceRT = nullptr;
    DummyKernel kernel{&dummyProgram, *function->getKernelInfoRT().weakRef<NEO::KernelInfo>(), deviceRT};
    NEO::PrintFormatter printfFormatter{kernel, *printfBuffer->allocationRT};
    printfFormatter.printKernelOutput();

    // reset to initial state after printing
    *reinterpret_cast<uint32_t *>(printfBuffer->getHostAddress()) = PrintfHandler::printfSurfaceInitialDataSize;
}

} // namespace L0
