
#include "runtime/program/program.h"

namespace NEO {

// Overriding NEO's behavior to allow for additional patchtokens to be serived in L0 driver
bool Program::isSafeToSkipUnhandledToken(unsigned int token) const {
    return true;
}

} // namespace NEO
