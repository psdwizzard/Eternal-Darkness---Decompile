typedef unsigned int u32;

extern void synthAddJob(void*, u32, u32);

void synthKeyStateUpdate(void* voice)
{
    synthAddJob(voice, 2, 0);
}
