#pragma once
#ifndef CMD_LIST_INTERNAL
#error "Don't #include this file directly."
#endif //CMD_LIST_INTERNAL

#include "cmdlist.h"

namespace L0 {

struct CommandListImp : public CommandList {
    xe_result_t destroy() override;

  protected:
    virtual ~CommandListImp() = default;
};

} // namespace L0
