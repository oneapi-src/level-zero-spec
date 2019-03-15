#include "encode_l3state.h"
#include "runtime/gen12hp/hw_cmds.h"
#include "runtime/gen12hp/hw_info.h"

namespace L0 {

template <>
const uint32_t EncodeL3State<IGFX_TIGERLAKE_HP>::offset = 0xB134;
//template <>
//const uint32_t EncodeL3State<IGFX_TIGERLAKE_HP>::offsetCCS = 0xB234;
template <>
const uint32_t EncodeL3State<IGFX_TIGERLAKE_HP>::data = 0xD0000020u;
template <>
const uint32_t EncodeL3State<IGFX_TIGERLAKE_HP>::dataSLM = 0xD0000020u;

} // namespace L0
