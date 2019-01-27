#include "event.h"

namespace xe {

struct EventImp : public Event {
};

Event *Event::create() {
    return new EventImp;
}

} // namespace xe
