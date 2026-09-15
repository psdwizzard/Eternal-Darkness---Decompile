typedef int s32;
typedef unsigned int u32;

volatile u32 __EXIRegs[15] : 0xCC006800;
#define REG(chan, index) (__EXIRegs[(chan) * 5 + (index)])

u32 fn_80206E8C(s32 chan, s32 exi, s32 tc, s32 ext)
{
    u32 cpr;
    u32 previous;

    cpr = REG(chan, 0);
    previous = cpr;
    cpr &= 0x7F5;
    if (exi != 0) {
        cpr |= 2;
    }
    if (tc != 0) {
        cpr |= 8;
    }
    if (ext != 0) {
        cpr |= 0x800;
    }
    REG(chan, 0) = cpr;
    return previous;
}
