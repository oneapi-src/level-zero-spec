#include "gmock/gmock.h"
#include "runtime/helpers/hw_info.h"
#include "runtime/helpers/options.h"
#include "runtime/os_interface/debug_settings_manager.h"
#include "runtime/platform/platform.h"
#include "unit_tests/tests_configuration.h"

PRODUCT_FAMILY productFamily = DEFAULT_PRODUCT_FAMILY;
GFXCORE_FAMILY renderCoreFamily;

namespace OCLRT {
extern bool overrideCommandStreamReceiverCreation;
extern TestMode testMode;
}

namespace L0 {
namespace ult {

extern ::testing::Environment *environment;

static OCLRT::HardwareInfo hwInfo = {};
static OCLRT::FeatureTable skuTable = {};
static GT_SYSTEM_INFO sysInfo = {};

struct Environment : public ::testing::Environment {
    void SetUp() override {
        if (OCLRT::DebugManager.flags.SetCommandStreamReceiver.get()) {
            OCLRT::overrideCommandStreamReceiverCreation = true;
            OCLRT::testMode = OCLRT::TestMode::AubTestsWithTbx;        
        }

        // Clone default device information
        assert(OCLRT::hardwareInfoTable[productFamily]);
        hwInfo = *OCLRT::hardwareInfoTable[productFamily];
        sysInfo = *hwInfo.pSysInfo;
        skuTable = *hwInfo.pSkuTable;

        productFamily = hwInfo.pPlatform->eProductFamily;
        renderCoreFamily = hwInfo.pPlatform->eRenderCoreFamily;

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
        environment = new Environment;
    }
};

static InitializeEnvironment initializeEnvironment;

} // namespace ult
} // namespace L0
