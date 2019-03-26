#include "runtime/aub/aub_helper.h"
#include "runtime/aub/aub_helper.inl"
#include "runtime/helpers/hw_helper.h"
#include "runtime/helpers/hw_helper_common.inl"
#include "runtime/helpers/flat_batch_buffer_helper_hw.inl"

namespace OCLRT {

#if defined(__linux__)
template <>
bool HwHelperHw<SKLFamily>::timestampPacketWriteSupported() const {
	return true;
}
#endif

} // namespace OCLRT
