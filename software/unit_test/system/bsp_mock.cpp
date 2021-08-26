#include "system_mock.h"

alt_u16 __builtin_ldhuio(void *src)
{
    throw -1;
    return 0;
}
alt_u8 __builtin_ldbuio(void *src)
{
    throw -1;
    return 0;
}

void __builtin_sthio(void *src, alt_u16 data)
{
    throw -1;
}
void __builtin_stbio(void *src, alt_u8 data)
{
   throw -1;
}

void __builtin_wrctl(alt_u32 reg, void *src)
{
    throw -1;
}
alt_u32 __builtin_rdctl(alt_u32 reg)
{
    throw -1;

    return 0;
}