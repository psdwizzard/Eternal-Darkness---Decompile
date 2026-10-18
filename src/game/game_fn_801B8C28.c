typedef unsigned int u32;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern unsigned char* seqSpeed(u32, u32);

void sndSeqSpeed(u32 handle, u32 value)
{
    hwDisableIrq();
    seqSpeed(handle, value);
    hwEnableIrq();
}
