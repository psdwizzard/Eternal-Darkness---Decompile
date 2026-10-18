extern unsigned char gTRKState[];
extern unsigned int lc_base;

unsigned int __TRK_get_MSR(void);

int TRKInitializeTarget(void)
{
    *(int *)(gTRKState + 0x98) = 1;
    *(unsigned int *)(gTRKState + 0x8C) = __TRK_get_MSR();
    lc_base = 0xE0000000;
    return 0;
}
