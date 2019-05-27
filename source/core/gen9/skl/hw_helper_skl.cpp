#include "runtime/aub/aub_helper_bdw_plus.inl"
#include "runtime/helpers/hw_helper_bdw_plus.inl"
#include "runtime/helpers/flat_batch_buffer_helper_hw.inl"

namespace NEO {

#if defined(__linux__)
template <> bool HwHelperHw<SKLFamily>::timestampPacketWriteSupported() const { return true; }
#endif

} // namespace NEO
