// This is a generated file
// Check E:\PROJECTS\OneAPI\level_zero\gerrit\loki\tests\unit_tests\test_module.cpp : 245 for details

#include "tests/unit_tests/mock_module_precompiled.h"

namespace L0 {
namespace ult {

static const uint32_t MemcpyBytes_SimdSize_Gen12HPcore = 32;

static const uint32_t MemcpyBytes_ISA_Gen12HPcore[] =
    {
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd,
        0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd, 0xcdcdcdcd};

static const uint32_t MemcpyBytes_CrossThreadDataBase_Gen12HPcore[] =
    {
        0x00000000, 0x00000000, 0x00000000, 0x00000020, 0x00000001, 0x00000001, 0x00000000, 0x00000000,
        0x862da000, 0x000001b3, 0x862dc000, 0x000001b3, 0x00000020, 0x00000001, 0x00000001, 0x00000000};

static const uint32_t MemcpyBytes_PerThreadDataBase_Gen12HPcore[] =
    {
        0x00010000, 0x00030002, 0x00050004, 0x00070006, 0x00090008, 0x000b000a, 0x000d000c, 0x000f000e,
        0x00110010, 0x00130012, 0x00150014, 0x00170016, 0x00190018, 0x001b001a, 0x001d001c, 0x001f001e,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};

static const uint32_t MemcpyBytes_BindingTableStateCount_Gen12HPcore = 0x2;

static const uint32_t MemcpyBytes_BindingTableOffsetGen12HPcore = 0x80;

static const size_t MemcpyBytes_SurfaceStateHeapSize_Gen12HPcore = 0x88;

static uint32_t MemcpyBytes_SurfaceStateHeap_Gen12HPcore[] =
    {
        0x87fd4000, 0x04000000, 0x001f007f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x862da000, 0x000001b3, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x87fd4000, 0x04000000, 0x001f007f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x862dc000, 0x000001b3, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000040};

static const size_t MemcpyBytes_DynamicStateHeapSize_Gen12HPcore = 0x20;

static const uint32_t MemcpyBytes_DynamicStateHeap_Gen12HPcore[] =
    {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000082, 0x00000000, 0x00000000, 0x00000002};

static const uint32_t MemcpyBytes_SamplerArrayDataBase_Gen12HPcore[] = {0xffffffff, 0x0, 0xffffffff};

static const bool MemcpyBytes_HasBarriers_Gen12HPcore = 0;

static const uint32_t MemcpyBytes_SlmSize_Gen12HPcore = 0x0;

static const bool MemcpyBytes_HasPrintfOutput_Gen12HPcore = 0;

static const std::pair<int, int> MemcpyBytes_BufferArgIndicesAndOffsets_Gen12HPcore[] = {
    {0x0, 0x20},
    {0x1, 0x28},
};

static const uint32_t MemcpyBytes_GroupSizeInPerThreadData_Gen12HPcore[] = {0x20, 0x1, 0x1};

static const PrecompiledFunctionMockData MemcpyBytes_Gen12HPcore{
    MemcpyBytes_SimdSize_Gen12HPcore,
    MemcpyBytes_ISA_Gen12HPcore, sizeof(MemcpyBytes_ISA_Gen12HPcore),
    MemcpyBytes_CrossThreadDataBase_Gen12HPcore, sizeof(MemcpyBytes_CrossThreadDataBase_Gen12HPcore),
    MemcpyBytes_PerThreadDataBase_Gen12HPcore, sizeof(MemcpyBytes_PerThreadDataBase_Gen12HPcore),
    MemcpyBytes_BindingTableStateCount_Gen12HPcore,
    MemcpyBytes_BindingTableOffsetGen12HPcore,
    MemcpyBytes_SurfaceStateHeapSize_Gen12HPcore,
    MemcpyBytes_SurfaceStateHeap_Gen12HPcore,
    MemcpyBytes_DynamicStateHeapSize_Gen12HPcore,
    MemcpyBytes_DynamicStateHeap_Gen12HPcore,
    MemcpyBytes_SamplerArrayDataBase_Gen12HPcore,
    MemcpyBytes_GroupSizeInPerThreadData_Gen12HPcore,
    MemcpyBytes_BufferArgIndicesAndOffsets_Gen12HPcore, sizeof(MemcpyBytes_BufferArgIndicesAndOffsets_Gen12HPcore) / sizeof(MemcpyBytes_BufferArgIndicesAndOffsets_Gen12HPcore[0]),
    MemcpyBytes_HasBarriers_Gen12HPcore,
    MemcpyBytes_SlmSize_Gen12HPcore,
    MemcpyBytes_HasPrintfOutput_Gen12HPcore};

RegisterPrecompiledFunctionMocksData Register_MemcpyBytes_Gen12HPcore{&MemcpyBytes_Gen12HPcore, "MemcpyBytes", "Gen12HPcore"};

} // namespace ult
} // namespace L0
