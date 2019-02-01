#pragma once
#ifndef CMD_LIST_INTERNAL
#error "Don't #include this file directly."
#endif //CMD_LIST_INTERNAL

#include "cmdlist.h"

namespace OCLRT {
class LinearStream;
}

namespace xe {

struct CommandListImp : public CommandList {
    CommandListImp(Device *device)
        : device(device),
          commandStream(nullptr) {
    }

    xe_result_t destroy() override;

    virtual bool initialize();

  protected:
    virtual ~CommandListImp();

    Device *device;
    OCLRT::LinearStream *commandStream;
};

} // namespace xe
