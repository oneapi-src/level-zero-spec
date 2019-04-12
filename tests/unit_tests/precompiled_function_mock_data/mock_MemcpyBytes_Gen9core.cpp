// This is a generated file
// Check TestBody for details

#include "tests/unit_tests/mock_module_precompiled.h"

namespace L0 {
namespace ult {

static const uint32_t MemcpyBytes_SimdSize_Gen9core = 32;

static const uint32_t MemcpyBytes_ISA_Gen9core[] = 
{
    0x00600001, 0x2060020c, 0x00200000, 0x00000000, 0x00008006, 0x30000004, 0x16001000, 0x04c004c0, 
    0x00000041, 0x20c00a2c, 0x0a000110, 0x00000064, 0x20004d01, 0x00037f07, 0x00800040, 0x20800a28, 
    0x120000c0, 0x00b10020, 0x00802040, 0x21200a28, 0x120000c0, 0x00b10040, 0x20019640, 0x07040b07, 
    0x00802040, 0x21a00a28, 0x0a8d0120, 0x000000e0, 0x0a800031, 0x21e00268, 0x06000160, 0x04210101, 
    0x20005601, 0x000b0407, 0x0a802031, 0x22200268, 0x060001a0, 0x04210101, 0x00802001, 0x21200208, 
    0x008d01a0, 0x00000000, 0x00800001, 0x22602208, 0x006001e0, 0x00000000, 0x00802001, 0x22a02208, 
    0x00600220, 0x00000000, 0x0a800033, 0x00013070, 0x00000082, 0x04030100, 0x0a802033, 0x00015070, 
    0x00000122, 0x04030100, 0x07600031, 0x20000204, 0x06000fe0, 0x82000010, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};


static const uint32_t MemcpyBytes_CrossThreadDataBase_Gen9core[] = 
{
    0x00000000, 0x00000000, 0x00000000, 0x00000020, 0x00000001, 0x00000001, 0x00000000, 0x00000000, 
    0xd944f000, 0x000055ba, 0xd945a000, 0x000055ba, 0x00000020, 0x00000001, 0x00000001, 0x00000000
};


static const uint32_t MemcpyBytes_PerThreadDataBase_Gen9core[] = 
{
    0x00010000, 0x00030002, 0x00050004, 0x00070006, 0x00090008, 0x000b000a, 0x000d000c, 0x000f000e, 
    0x00110010, 0x00130012, 0x00150014, 0x00170016, 0x00190018, 0x001b001a, 0x001d001c, 0x001f001e, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};


static const uint32_t MemcpyBytes_BindingTableStateCount_Gen9core = 0x2;

static const uint32_t MemcpyBytes_BindingTableOffsetGen9core = 0x80;

static const size_t MemcpyBytes_SurfaceStateHeapSize_Gen9core = 0x88;

static uint32_t MemcpyBytes_SurfaceStateHeap_Gen9core[] =
{
    0x87fd4000, 0x04000000, 0x001f007f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0xd8630000, 0x00005642, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x87fd4000, 0x04000000, 0x001f007f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0xd85ee000, 0x00005642, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000040
};


static const size_t MemcpyBytes_DynamicStateHeapSize_Gen9core = 0x20;

static const uint32_t MemcpyBytes_DynamicStateHeap_Gen9core[] =
{
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000082, 0x00000000, 0x00000000, 0x00000002
};


static const uint32_t MemcpyBytes_SamplerArrayDataBase_Gen9core[] =
{
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};


static const bool MemcpyBytes_HasBarriers_Gen9core = 0;

static const uint32_t MemcpyBytes_SlmSize_Gen9core = 0x0;

static const bool MemcpyBytes_HasPrintfOutput_Gen9core = 0;

static const std::pair<int, int> MemcpyBytes_BufferArgIndicesAndOffsets_Gen9core[] = { {0x0, 0x20}, {0x1, 0x28},  };

static const uint32_t MemcpyBytes_GroupSizeInPerThreadData_Gen9core[] = { 0x20, 0x1, 0x1 };

static const PrecompiledFunctionMockData MemcpyBytes_Gen9core {
MemcpyBytes_SimdSize_Gen9core,
MemcpyBytes_ISA_Gen9core, sizeof(MemcpyBytes_ISA_Gen9core),
MemcpyBytes_CrossThreadDataBase_Gen9core, sizeof(MemcpyBytes_CrossThreadDataBase_Gen9core),
MemcpyBytes_PerThreadDataBase_Gen9core, sizeof(MemcpyBytes_PerThreadDataBase_Gen9core),
MemcpyBytes_BindingTableStateCount_Gen9core,
MemcpyBytes_BindingTableOffsetGen9core,
MemcpyBytes_SurfaceStateHeapSize_Gen9core,
MemcpyBytes_SurfaceStateHeap_Gen9core,
MemcpyBytes_DynamicStateHeapSize_Gen9core,
MemcpyBytes_DynamicStateHeap_Gen9core,
MemcpyBytes_SamplerArrayDataBase_Gen9core,
MemcpyBytes_GroupSizeInPerThreadData_Gen9core,
MemcpyBytes_BufferArgIndicesAndOffsets_Gen9core, sizeof(MemcpyBytes_BufferArgIndicesAndOffsets_Gen9core) / sizeof(MemcpyBytes_BufferArgIndicesAndOffsets_Gen9core[0]),
MemcpyBytes_HasBarriers_Gen9core,
MemcpyBytes_SlmSize_Gen9core,
MemcpyBytes_HasPrintfOutput_Gen9core
};

RegisterPrecompiledFunctionMocksData Register_MemcpyBytes_Gen9core{ & MemcpyBytes_Gen9core, "MemcpyBytes", "Gen9core" }; 

} // namespace L0
} // namespace ult
