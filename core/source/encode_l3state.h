#pragma once
#include "encode_flush.h"
#include "encode_set_mmio.h"

namespace L0 {

template <PRODUCT_FAMILY productFamily>
struct EncodeL3State : ToGfxCoreFamily<productFamily> {
    using BaseClass = ToGfxCoreFamily<productFamily>;
    using BaseClass::gfxCoreFamily;

    static const uint32_t offset;
    static const uint32_t data;
    static const uint32_t dataSLM;

    static const size_t size =
        EncodeFlush<gfxCoreFamily>::size +
        EncodeSetMMIO<gfxCoreFamily>::size;

    static void append(CommandContainer &container, bool enableSLM) {
        EncodeFlush<gfxCoreFamily>::append(container);
        EncodeSetMMIO<gfxCoreFamily>::append(container,
                                             offset,
                                             enableSLM ? dataSLM : data);
    }
};

} // namespace L0
