typedef unsigned int u32;

extern void synthAddJob(void*, u32, u32);

void synthForceLowPrecisionUpdate(void* voice)
{
    synthAddJob(voice, 0, 0);
    synthAddJob(voice, 1, 0);
}
