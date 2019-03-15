#include "sampler.h"

namespace L0 {

class SamplerImp : public Sampler {
  public:
    xe_result_t destroy() override;
};

xe_result_t SamplerImp::destroy() {
    delete this;
    return XE_RESULT_SUCCESS;
}

Sampler *Sampler::create(Device *device) {
    return new SamplerImp;
}

} // namespace L0
