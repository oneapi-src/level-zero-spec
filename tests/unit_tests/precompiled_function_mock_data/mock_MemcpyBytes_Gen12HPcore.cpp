// This is a generated file
// Check TestBody for details

#include "tests/unit_tests/mock_module_precompiled.h"

namespace L0 {
namespace ult {

static const uint32_t MemcpyBytes_SimdSize_Gen12HPcore = 32;

static const uint32_t MemcpyBytes_ISA_Gen12HPcore[] = 
{
    0x80030061, 0x7f054220, 0x00000000, 0x00000000, 0x80000065, 0x7f458220, 0x02000004, 0xffffffe0, 
    0x80000065, 0x7f058110, 0x01000044, 0x00ff00ff, 0x80001a40, 0x7f458220, 0x01007f44, 0x00400040, 
    0x8000195b, 0x7f448220, 0x01017f44, 0x00c07f04, 0x80039031, 0x01240000, 0xa9fa7f0c, 0x02100000, 
    0x80003040, 0x7f458220, 0x01007f44, 0x00800080, 0x80039131, 0x05140000, 0xa7fa7f0c, 0x02100000, 
    0x80033161, 0x7f054220, 0x00000000, 0x00000000, 0x80000065, 0x7f458220, 0x02000004, 0xffffffe0, 
    0x80039231, 0x07140000, 0xa7fa7f0c, 0x02100000, 0x80032061, 0x03050220, 0x00100004, 0x00000000, 
    0x80000966, 0x80018220, 0x01008000, 0x04c004c0, 0xe8002201, 0x00010001, 0x80000941, 0x20010660, 
    0x01000884, 0x00000324, 0x80000049, 0x04050660, 0x06000884, 0x00000324, 0x80030061, 0x7f050aa0, 
    0x00460305, 0x00000000, 0x00041952, 0x0b040660, 0x090e0404, 0x07040105, 0x00240052, 0x0d040660, 
    0x090e0404, 0x07040205, 0x0004a331, 0x0f140000, 0xa2020b14, 0x00400000, 0x00249431, 0x11140000, 
    0xa2020d14, 0x00400000, 0x00042161, 0x05050aa0, 0x00460b05, 0x00000000, 0x00240061, 0x09050aa0, 
    0x00460d05, 0x00000000, 0x00042361, 0x13050020, 0x00300f04, 0x00000000, 0x00242461, 0x15050020, 
    0x00301104, 0x00000000, 0x0004a531, 0x00000000, 0xa2000514, 0x00c01314, 0x00249631, 0x00000000, 
    0xa2000914, 0x00c01514, 0x80030b31, 0x00000004, 0x70207f0c, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};


static const uint32_t MemcpyBytes_CrossThreadDataBase_Gen12HPcore[] = 
{
    0x00000000, 0x00000000, 0x00000000, 0x00000020, 0x00000001, 0x00000001, 0x00000000, 0x00000000, 
    0x555aa000, 0x000055eb, 0x55602000, 0x000055eb, 0x00000020, 0x00000001, 0x00000001, 0x00000000
};


static const uint32_t MemcpyBytes_PerThreadDataBase_Gen12HPcore[] = 
{
    0x00010000, 0x00030002, 0x00050004, 0x00070006, 0x00090008, 0x000b000a, 0x000d000c, 0x000f000e, 
    0x00110010, 0x00130012, 0x00150014, 0x00170016, 0x00190018, 0x001b001a, 0x001d001c, 0x001f001e, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};


static const uint32_t MemcpyBytes_BindingTableStateCount_Gen12HPcore = 0x2;

static const uint32_t MemcpyBytes_BindingTableOffsetGen12HPcore = 0x80;

static const size_t MemcpyBytes_SurfaceStateHeapSize_Gen12HPcore = 0x88;

static uint32_t MemcpyBytes_SurfaceStateHeap_Gen12HPcore[] =
{
    0x87fd4000, 0x04000000, 0x001f007f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0xe3fdd000, 0x000055a6, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x87fd4000, 0x04000000, 0x001f007f, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0xe4724000, 0x000055a6, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000040
};


static const size_t MemcpyBytes_DynamicStateHeapSize_Gen12HPcore = 0x20;

static const uint32_t MemcpyBytes_DynamicStateHeap_Gen12HPcore[] =
{
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000082, 0x00000000, 0x00000000, 0x00000002
};


static const uint32_t MemcpyBytes_SamplerArrayDataBase_Gen12HPcore[] =
{
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};


static const bool MemcpyBytes_HasBarriers_Gen12HPcore = 0;

static const uint32_t MemcpyBytes_SlmSize_Gen12HPcore = 0x0;

static const bool MemcpyBytes_HasPrintfOutput_Gen12HPcore = 0;

static const std::pair<int, int> MemcpyBytes_BufferArgIndicesAndOffsets_Gen12HPcore[] = { {0x0, 0x20}, {0x1, 0x28},  };

static const uint32_t MemcpyBytes_GroupSizeInPerThreadData_Gen12HPcore[] = { 0x20, 0x1, 0x1 };

static const PrecompiledFunctionMockData MemcpyBytes_Gen12HPcore {
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
MemcpyBytes_HasPrintfOutput_Gen12HPcore
};

RegisterPrecompiledFunctionMocksData Register_MemcpyBytes_Gen12HPcore{ & MemcpyBytes_Gen12HPcore, "MemcpyBytes", "Gen12HPcore" }; 

} // namespace L0
} // namespace ult
