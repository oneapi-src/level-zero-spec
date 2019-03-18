#include "device.h"
#include "event.h"
#include "runtime/os_interface/linux/os_interface.h"

namespace L0 {

class DrmEvent : public Event {
public:
    DrmEvent(void *execEnvRT) :
        execEnvRT(execEnvRT) {
        }
    bool waitForFlushStamp(FlushStamp &flushStamp) override;

protected:
    void *execEnvRT = nullptr;
};

} //namespace L0
