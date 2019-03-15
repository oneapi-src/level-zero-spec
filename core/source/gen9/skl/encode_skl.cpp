#include "encode_l3state.h"
#include "runtime/gen9/hw_cmds.h"
#include "runtime/gen9/hw_info.h"

namespace L0 {

template <>
const uint32_t EncodeL3State<IGFX_SKYLAKE>::offset = 0x7034;
template <>
const uint32_t EncodeL3State<IGFX_SKYLAKE>::data = 0x80000140u;
template <>
const uint32_t EncodeL3State<IGFX_SKYLAKE>::dataSLM = 0x60000121u;

}
