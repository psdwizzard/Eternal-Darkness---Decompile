typedef unsigned int u32;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern void seqVolume(u32, u32, u32, u32);

void sndSeqVolume(u32 handle, u32 value1, u32 value2, u32 value3)
{
    hwDisableIrq();
    seqVolume(handle, value1, value2, value3);
    hwEnableIrq();
}
