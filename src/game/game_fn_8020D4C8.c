typedef int BOOL;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 __OSMaskInterrupts(u32 interrupts);

volatile u16 __MEMRegs[64] : 0xCC004000;

BOOL fn_8020D4C8(BOOL final)
{
    if (final) {
        __MEMRegs[8] = 0xFF;
        __OSMaskInterrupts(0xF0000000);
    }
    return 1;
}
