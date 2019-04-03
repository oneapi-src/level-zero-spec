#include "mock_device.h"
#include "mock_memory_manager.h"
#include "mock_mocs_mapper.h"
#include "runtime/device/device.h"
#include "runtime/platform/platform.h"
#include "unit_tests/mocks/mock_csr.h"
#include "gmock/gmock.h"

namespace L0 {
namespace ult {

using ::testing::Return;

Mock<Device>::Mock() {
    auto ordinal = 0u;
    auto platform = NEO::constructPlatform();
    auto success = platform->initialize();
    assert(success);
    auto deviceRT = platform->getDevice(ordinal);
    this->deviceRT = deviceRT;
    assert(deviceRT);
    auto executionEnvironment = deviceRT->getExecutionEnvironment();
    assert(executionEnvironment);

    csrRT = new MockCommandStreamReceiver(*executionEnvironment);

    static ::testing::NiceMock<Mock<MemoryManager>> memoryManager;
    EXPECT_CALL(*this, getMemoryManager)
        .WillRepeatedly(Return(&memoryManager));

    static ::testing::NiceMock<Mock<MOCSMapper>> mocsMapper;
    static PtrRef<L0::MOCSMapper> mocsMapperRef{&mocsMapper};
    EXPECT_CALL(*this, getMOCSMapper)
        .WillRepeatedly(Return(mocsMapperRef));
}

Mock<Device>::~Mock() {
    delete static_cast<MockCommandStreamReceiver *>(csrRT);
}

} // namespace ult
} // namespace L0
