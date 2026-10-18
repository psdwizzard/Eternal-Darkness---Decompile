typedef unsigned int u32;
typedef unsigned long long u64;
extern u64 synthRealTime;
extern void synthAddJob(void*, u32, u32);

void synthStartSynthJobHandling(void* voice)
{
    *(u64*)((unsigned char*)voice + 0x24) = synthRealTime;
    *(u64*)((unsigned char*)voice + 0x2C) = synthRealTime;
    synthAddJob(voice, 0, 0);
    synthAddJob(voice, 1, 0);
}
