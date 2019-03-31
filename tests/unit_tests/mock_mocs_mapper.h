#pragma once
#include "mocs_mapper.h"

#include "mock.h"
#include "white_box.h"

namespace L0 {
namespace ult {

template <>
struct WhiteBox<::L0::MOCSMapper> : public ::L0::MOCSMapper {
    using ::L0::MOCSMapper::MOCSMapper;
};

using MOCSMapper = WhiteBox<::L0::MOCSMapper>;

template <>
struct Mock<MOCSMapper> : MOCSMapper {
    Mock() : L0::ult::MOCSMapper(nullptr) {
        // Note : don't add odd values, youngest bit is shared with "EncryptedData" flag
        ON_CALL(*this, getUncachedMOCS)
            .WillByDefault(::testing::Return(0));

        ON_CALL(*this, getFullyCachedMOCS)
            .WillByDefault(::testing::Return(2));

        ON_CALL(*this, getCachedInstructionHeapMOCS)
            .WillByDefault(::testing::Return(4));

        ON_CALL(*this, getCachedStateHeapMOCS)
            .WillByDefault(::testing::Return(6));

        EXPECT_CALL(*this, getUncachedMOCS()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getFullyCachedMOCS()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getCachedInstructionHeapMOCS()).Times(::testing::AnyNumber());
        EXPECT_CALL(*this, getCachedStateHeapMOCS()).Times(::testing::AnyNumber());
    }

    ~Mock() = default;

    MOCK_CONST_METHOD0(getUncachedMOCS, uint32_t());
    MOCK_CONST_METHOD0(getFullyCachedMOCS, uint32_t());
    MOCK_CONST_METHOD0(getCachedInstructionHeapMOCS, uint32_t());
    MOCK_CONST_METHOD0(getCachedStateHeapMOCS, uint32_t());
};

} // namespace ult
} // namespace L0
