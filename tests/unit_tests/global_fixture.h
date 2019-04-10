#pragma once
#include "memory_manager.h"
#include "mock_memory_manager.h"
#include "test.h"

namespace L0 {

extern MemoryManager *globalMemoryManager;

namespace ult {

class GlobalFixtureTest: public ::testing::Test {
  public:
    void SetUp() override {
        globalMemoryManager_prev = globalMemoryManager;
        globalMemoryManager = &globalMemoryManager_mock;
    }

    void TearDown() override {
        globalMemoryManager = globalMemoryManager_prev;
    }

    Mock<MemoryManager> globalMemoryManager_mock;
    L0::MemoryManager *globalMemoryManager_prev;
};

} // namespace ult
} // namespace L0
