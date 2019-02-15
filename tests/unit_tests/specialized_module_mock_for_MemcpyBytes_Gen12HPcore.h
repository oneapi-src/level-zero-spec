#pragma once

static const uint32_t MemcpyBytes_SimdSize_Gen12HPcore = 32;

static const uint32_t MemcpyBytes_ISA_Gen12HPcore[] = 
{
    0x80030061, 0x7f054220, 0x00000000, 0x00000000, 0x80000065, 0x7f458220, 0x02000004, 0xffffffe0, 
    0x80000065, 0x7f058110, 0x01000044, 0x00ff00ff, 0x80000240, 0x7f458220, 0x01007f44, 0x00400040, 
    0x8000015b, 0x7f448220, 0x01017f44, 0x00c07f04, 0x80039031, 0x01240000, 0xa9fa7f0c, 0x02100000, 
    0x80003040, 0x7f458220, 0x01007f44, 0x00800080, 0x80039131, 0x05140000, 0xa7fa7f0c, 0x02100000, 
    0x80033161, 0x7f054220, 0x00000000, 0x00000000, 0x80000065, 0x7f458220, 0x02000004, 0xffffffe0, 
    0x80039231, 0x07140000, 0xa7fa7f0c, 0x02100000, 0x80032061, 0x03050220, 0x00100004, 0x00000000, 
    0x80000066, 0x80018220, 0x01008000, 0x04c004c0, 0x8000a241, 0x20010660, 0x01000884, 0x00000324, 
    0x80030061, 0x7f050aa0, 0x00460305, 0x00000000, 0x80000049, 0x04050660, 0x06000884, 0x00000324, 
    0x00049152, 0x05040968, 0x06060105, 0x07040404, 0x00240052, 0x09040968, 0x06060205, 0x07040404, 
    0x00030261, 0x23060220, 0x00460505, 0x00000000, 0x00130061, 0x25060220, 0x00460605, 0x00000000, 
    0x00230361, 0x27060220, 0x00460905, 0x00000000, 0x00330061, 0x29060220, 0x00460a05, 0x00000000, 
    0x00030440, 0x0b050770, 0x02000844, 0x00202304, 0x00130440, 0x0d050770, 0x02000844, 0x00202504, 
    0x00230440, 0x0f050770, 0x02000844, 0x00202704, 0x00330440, 0x11050770, 0x02000844, 0x00202904, 
    0x0004b331, 0x13140000, 0xc1fe0b24, 0x01040000, 0x00249431, 0x15140000, 0xc1fe0f24, 0x01040000, 
    0x00030040, 0x17050770, 0x02000804, 0x00202304, 0x00130040, 0x19050770, 0x02000804, 0x00202504, 
    0x00230040, 0x1b050770, 0x02000804, 0x00202704, 0x00330040, 0x1d050770, 0x02000804, 0x00202904, 
    0x00042361, 0x1f050020, 0x00301304, 0x00000000, 0x00242461, 0x21050020, 0x00301504, 0x00000000, 
    0x0004a531, 0x00000000, 0xc1fe1724, 0x01a41f14, 0x00249631, 0x00000000, 0xc1fe1b24, 0x01a42114, 
    0x80034731, 0x2b0c0000, 0xa000030c, 0x02780000, 0x80032761, 0x2b050aa0, 0x00462b05, 0x00000000, 
    0x80030031, 0x00000004, 0x70207f0c, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};


static const uint32_t MemcpyBytes_CrossThreadDataBase_Gen12HPcore[] = 
{
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
    0xf0990000, 0x000002a1, 0xf09c0000, 0x000002a1, 0x00000000, 0x00000000, 0x00000000, 0x00000000};


static const std::pair<int, int> MemcpyBytes_BufferArgIndicesAndOffsets_Gen12HPcore[] = { {0x0, 0x20}, {0x1, 0x28},  };

