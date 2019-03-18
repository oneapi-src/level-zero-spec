#include "device.h"
#include "event.h"

namespace L0 {

class WddmEvent : public Event {
public:
    WddmEvent(void *execEnvRT) :
        execEnvRT(execEnvRT) {
        }
    bool waitForFlushStamp(FlushStamp &flushStamp) override;

protected:
    void *execEnvRT = nullptr;
};

} //namespace L0
