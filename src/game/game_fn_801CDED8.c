typedef unsigned int u32;

extern u32 salDspIsDone;
extern u32 salDspInitIsDone;

void dspInitCallback(void)
{
    salDspIsDone = 1;
    salDspInitIsDone = 1;
}
