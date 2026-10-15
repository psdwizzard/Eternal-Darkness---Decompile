typedef unsigned long u32;

extern void *memset(void *dest, int value, unsigned long size);
extern unsigned char lbl_80642BF8[24];

volatile u32 __EXIRegs[15] : 0xCC006800;
extern volatile u32 __SIRegs[64] : 0xCC006400;

void fn_8022E0E0(void)
{
    memset(lbl_80642BF8, 0, sizeof(lbl_80642BF8));
    __EXIRegs[10] = 0;
    __SIRegs[15] = 0;
}
