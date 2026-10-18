typedef unsigned int u32;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern void seqMute(u32, u32, u32);

void sndSeqMute(u32 handle, u32 value1, u32 value2)
{
    hwDisableIrq();
    seqMute(handle, value1, value2);
    hwEnableIrq();
}
