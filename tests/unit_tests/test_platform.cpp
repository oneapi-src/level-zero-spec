#include "gmock/gmock.h"
#include "runtime/helpers/options.h"
#include "runtime/platform/platform.h"
#include "runtime/helpers/hw_info.h"

static OCLRT::HardwareInfo hwInfo = {};
static OCLRT::FeatureTable skuTable = {};
static GT_SYSTEM_INFO sysInfo = {};

static void initializeHardwareInfo() {
    // Clone default device information
    hwInfo = *OCLRT::platformDevices[0];
    sysInfo = *hwInfo.pSysInfo;
    skuTable = *hwInfo.pSkuTable;

    // Disable mid-thread preemption
    hwInfo.capabilityTable.defaultPreemptionMode = OCLRT::PreemptionMode::ThreadGroup;

    // Initialize hardwareInfo
    OCLRT::hardwareInfoSetup[IGFX_SKYLAKE](&sysInfo, &skuTable, false, "default");

    // Replace original hardwareInfo with our clone
    hwInfo.pSysInfo = &sysInfo;
    hwInfo.pSkuTable = &skuTable;
    OCLRT::platformDevices[0] = &hwInfo;
}

TEST(platformInitialize, shouldSucceed) {
    initializeHardwareInfo();

    auto platform = OCLRT::constructPlatform();
    bool ret = platform->initialize();
    ASSERT_TRUE(ret);
    ASSERT_NE(nullptr, platform);

    EXPECT_TRUE(platform->isInitialized());
}
