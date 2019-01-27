#include "cmd_list.h"

namespace xe {

struct CommandListImp : public CommandList {
};

CommandList *CommandList::create() {
    return new CommandListImp;
}

} // namespace xe
