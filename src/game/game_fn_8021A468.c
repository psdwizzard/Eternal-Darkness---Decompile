typedef unsigned int u32;

volatile u32 __AIRegs[8] : 0xCC006C00;

void fn_8021A468(u32 volume) {
    __AIRegs[1] = (__AIRegs[1] & ~0xFFu) | (volume & 0xFFu);
}
