#include "gmock/gmock.h"
#include "runtime/helpers/hw_info.h"
#include "runtime/helpers/options.h"
#include "runtime/os_interface/debug_settings_manager.h"
#include "runtime/platform/platform.h"
#include "unit_tests/tests_configuration.h"

PRODUCT_FAMILY productFamily = DEFAULT_PRODUCT_FAMILY;
GFXCORE_FAMILY renderCoreFamily;

namespace NEO {
extern bool overrideCommandStreamReceiverCreation;
extern TestMode testMode;
} // namespace NEO

namespace L0 {
namespace ult {

extern ::testing::Environment *environment;

static NEO::HardwareInfo hwInfo = {};
static NEO::FeatureTable skuTable = {};
static GT_SYSTEM_INFO sysInfo = {};

struct Environment : public ::testing::Environment {
    void SetUp() override {
        if (NEO::DebugManager.flags.SetCommandStreamReceiver.get()) {
            NEO::overrideCommandStreamReceiverCreation = false;
            NEO::testMode = NEO::TestMode::AubTestsWithTbx;
        }

        // Clone default device information
        assert(NEO::hardwareInfoTable[productFamily]);
        hwInfo = *NEO::hardwareInfoTable[productFamily];
        sysInfo = hwInfo.gtSystemInfo;
        skuTable = hwInfo.featureTable;

        productFamily = hwInfo.platform.eProductFamily;
        renderCoreFamily = hwInfo.platform.eRenderCoreFamily;

        // Disable mid-thread preemption
        hwInfo.capabilityTable.defaultPreemptionMode = NEO::PreemptionMode::ThreadGroup;

        // Initialize hardwareInfo
        NEO::hardwareInfoSetup[productFamily](&hwInfo, true, "default");

        NEO::platformDevices[0] = &hwInfo;
    }
};

struct InitializeEnvironment {
    InitializeEnvironment() { environment = new Environment; }
};

static InitializeEnvironment initializeEnvironment;

} // namespace ult
} // namespace L0
