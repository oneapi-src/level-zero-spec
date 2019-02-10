#include "gmock/gmock.h"
#include "runtime/helpers/options.h"
#include "runtime/platform/platform.h"
#include "runtime/helpers/hw_info.h"
#include "unit_tests/tests_configuration.h"

GFXCORE_FAMILY renderCoreFamily = IGFX_GEN9_CORE;
PRODUCT_FAMILY productFamily = IGFX_SKYLAKE;

namespace OCLRT {
extern TestMode testMode;
}

namespace xe {
namespace ult {

static OCLRT::HardwareInfo hwInfo = {};
static OCLRT::FeatureTable skuTable = {};
static GT_SYSTEM_INFO sysInfo = {};

struct Environment : public ::testing::Environment {
    void SetUp() override {
        OCLRT::testMode = OCLRT::TestMode::AubTestsWithTbx;

        // Clone default device information
        hwInfo = *OCLRT::platformDevices[0];
        sysInfo = *hwInfo.pSysInfo;
        skuTable = *hwInfo.pSkuTable;

        // Disable mid-thread preemption
        hwInfo.capabilityTable.defaultPreemptionMode = OCLRT::PreemptionMode::ThreadGroup;

        // Initialize hardwareInfo
        OCLRT::hardwareInfoSetup[productFamily](&sysInfo, &skuTable, true, "default");

        // Replace original hardwareInfo with our clone
        hwInfo.pSysInfo = &sysInfo;
        hwInfo.pSkuTable = &skuTable;
        OCLRT::platformDevices[0] = &hwInfo;
    }
};

struct InitializeEnvironment {
    InitializeEnvironment() {
        extern ::testing::Environment *environment;

        environment = new Environment;
    }
};

static InitializeEnvironment initializeEnvironment;

} // namespace ult
} // namespace xe
