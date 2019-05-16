#include "mock_cmdlist.h"
#include "mock_device.h"
#include "mock_memory_manager.h"
#include "mock_mocs_mapper.h"
#include "event.h"
#include "graphics_allocation.h"
#include "igfxfmid.h"
#include "runtime/command_stream/linear_stream.h"
#include "runtime/indirect_heap/indirect_heap.h"
#include "test.h"
#include "unit_tests/gen_common/gen_cmd_parse.h"
#include "global_fixture.h"

namespace L0 {
namespace ult {

TEST(xeCommandListDestroy, redirectsToObject) {
    Mock<CommandList> cmdList;
    EXPECT_CALL(cmdList, destroy()).Times(1);

    auto result = xeCommandListDestroy(cmdList.toHandle());
    EXPECT_EQ(XE_RESULT_SUCCESS, result);
}

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;

class CommandListCreate : public GlobalFixtureTest {};

TEST_F(CommandListCreate, returnsCommandListOnSuccess) {
    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList);

    EXPECT_EQ(&device, commandList->device);
    ASSERT_NE(commandList->allocation, nullptr);
    auto numAllocations = 0u;

    auto allocation = whitebox_cast(commandList->allocation);
    ++numAllocations;

    ASSERT_NE(nullptr, commandList->commandStream);
    for (auto indirectHeap : commandList->indirectHeaps) {
        ASSERT_NE(indirectHeap, nullptr);
    }

    for (auto allocationIndirectHeap : commandList->allocationIndirectHeaps) {
        ++numAllocations;
        ASSERT_NE(allocationIndirectHeap, nullptr);
    }

    EXPECT_LT(0u, commandList->commandStream->getAvailableSpace());
    ASSERT_EQ(commandList->residencyContainer.size(), numAllocations);
    EXPECT_EQ(commandList->residencyContainer.front(), allocation->allocationRT);
    commandList->destroy();
}

TEST_F(CommandListCreate, givenInvalidProductFamilyReturnsNullPointer) {
    Mock<Device> device;
    auto commandList = CommandList::create(IGFX_UNKNOWN, &device);
    EXPECT_EQ(nullptr, commandList);
}

HWTEST_F(CommandListCreate, addsStateBaseAddressToBatchBuffer) {
    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->close();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
    using STATE_BASE_ADDRESS = typename FamilyType::STATE_BASE_ADDRESS;
    auto itor = find<STATE_BASE_ADDRESS *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        auto cmd = genCmdCast<STATE_BASE_ADDRESS *>(*itor);

        auto heap = commandList->indirectHeaps[CommandList::DYNAMIC_STATE];
        EXPECT_TRUE(cmd->getDynamicStateBaseAddressModifyEnable());
        EXPECT_EQ(cmd->getDynamicStateBaseAddress(), heap->getHeapGpuBase());
        EXPECT_TRUE(cmd->getDynamicStateBufferSizeModifyEnable());
        EXPECT_EQ(cmd->getDynamicStateBufferSize(), heap->getMaxAvailableSpace());

        EXPECT_TRUE(cmd->getInstructionBaseAddressModifyEnable());
        EXPECT_EQ(cmd->getInstructionBaseAddress(),
                  device.getMemoryManager()->getIsaHeapGpuAddress());
        EXPECT_TRUE(cmd->getInstructionBufferSizeModifyEnable());
        EXPECT_EQ(cmd->getInstructionBufferSize(), MemoryConstants::sizeOf4GBinPageEntities);

        heap = commandList->indirectHeaps[CommandList::GENERAL_STATE];
        EXPECT_TRUE(cmd->getGeneralStateBaseAddressModifyEnable());
        EXPECT_EQ(cmd->getGeneralStateBaseAddress(), heap->getHeapGpuBase());
        EXPECT_TRUE(cmd->getGeneralStateBufferSizeModifyEnable());
        EXPECT_EQ(cmd->getGeneralStateBufferSize(), heap->getMaxAvailableSpace());

        heap = commandList->indirectHeaps[CommandList::INDIRECT_OBJECT];
        EXPECT_TRUE(cmd->getIndirectObjectBaseAddressModifyEnable());
        EXPECT_EQ(cmd->getIndirectObjectBaseAddress(), heap->getHeapGpuBase());
        EXPECT_TRUE(cmd->getIndirectObjectBufferSizeModifyEnable());
        EXPECT_EQ(cmd->getIndirectObjectBufferSize(), heap->getMaxAvailableSpace());

        heap = commandList->indirectHeaps[CommandList::SURFACE_STATE];
        EXPECT_TRUE(cmd->getSurfaceStateBaseAddressModifyEnable());
        EXPECT_EQ(cmd->getSurfaceStateBaseAddress(), heap->getHeapGpuBase());

        auto mocsMapper = device.getMOCSMapper();
        EXPECT_EQ(mocsMapper->getCachedInstructionHeapMOCS(),
                  cmd->getInstructionMemoryObjectControlState());
        EXPECT_EQ(mocsMapper->getFullyCachedMOCS(),
                  cmd->getStatelessDataPortAccessMemoryObjectControlState());
    }
}

HWTEST2_F(CommandListCreate, addsBindingTablePoolAllocToBatchBuffer, IsGen12HP) {
    Mock<Device> device;

    auto commandList = whitebox_cast(CommandList::create(productFamily, &device));
    ASSERT_NE(nullptr, commandList->commandStream);
    auto usedSpaceBefore = commandList->commandStream->getUsed();

    auto result = commandList->close();
    ASSERT_EQ(XE_RESULT_SUCCESS, result);

    auto usedSpaceAfter = commandList->commandStream->getUsed();
    ASSERT_GT(usedSpaceAfter, usedSpaceBefore);

    GenCmdList cmdList;
    ASSERT_TRUE(FamilyType::PARSE::parseCommandBuffer(
        cmdList, ptrOffset(commandList->commandStream->getCpuBase(), 0), usedSpaceAfter));
    using _3DSTATE_BINDING_TABLE_POOL_ALLOC =
        typename FamilyType::_3DSTATE_BINDING_TABLE_POOL_ALLOC;
    auto itor = find<_3DSTATE_BINDING_TABLE_POOL_ALLOC *>(cmdList.begin(), cmdList.end());
    ASSERT_NE(cmdList.end(), itor);

    {
        const auto &heap = commandList->getIndirectHeap(CommandContainer::SURFACE_STATE);

        auto cmd = genCmdCast<_3DSTATE_BINDING_TABLE_POOL_ALLOC *>(*itor);
        EXPECT_EQ(heap.getHeapGpuBase(), cmd->getBindingTablePoolBaseAddress());
        EXPECT_EQ(heap.getHeapSizeInPages(), cmd->getBindingTablePoolBufferSize());

        auto mocsMapper = device.getMOCSMapper();
        EXPECT_EQ(mocsMapper->getCachedStateHeapMOCS(),
                  cmd->getSurfaceObjectControlStateIndexToMocsTables());
    }
}

} // namespace ult
} // namespace L0
