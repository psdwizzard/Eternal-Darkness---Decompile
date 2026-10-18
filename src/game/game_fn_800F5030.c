extern unsigned char gTRKCPUState[];
extern unsigned int lc_base;

unsigned int TRKTargetTranslate(unsigned int address)
{
    unsigned int base = lc_base;

    if (address >= base && address < base + 0x4000 &&
        (*(unsigned int *)(gTRKCPUState + 0x238) & 3) != 0) {
        return address;
    }
    return (address & 0x3FFFFFFF) | 0x80000000;
}
