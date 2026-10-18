typedef unsigned int u32;

extern u32 dspHRTFOn;

void hwDisableHRTF(void)
{
    dspHRTFOn = 0;
}
