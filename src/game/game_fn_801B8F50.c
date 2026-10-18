extern void hwDisableIrq(void);
extern void seqKillAllInstances(void);
extern void s3dKillAllEmitter(void);
extern void synthKillAllVoices(int);
extern void hwEnableIrq(void);

void sndSilence(void)
{
    hwDisableIrq();
    seqKillAllInstances();
    s3dKillAllEmitter();
    synthKillAllVoices(0);
    hwEnableIrq();
}
