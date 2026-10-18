typedef unsigned int u32;

extern void hwDisableIrq(void);
extern void hwEnableIrq(void);
extern void seqContinue(u32);

void sndSeqContinue(u32 handle)
{
    hwDisableIrq();
    seqContinue(handle);
    hwEnableIrq();
}
