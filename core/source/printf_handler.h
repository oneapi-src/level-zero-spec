#pragma once

namespace OCLRT {
class PrintfHandler;
}

namespace L0 {

class PrintfHandler {
  public:
    PrintfHandler(Device *device){};

  protected:
    PrintfHandler(const PrintfHandler &) = delete;
    PrintfHandler &operator=(PrintfHandler const &) = delete;

    OCLRT::PrintfHandler *printfHandlerRT = nullptr;
};

} // namespace L0
