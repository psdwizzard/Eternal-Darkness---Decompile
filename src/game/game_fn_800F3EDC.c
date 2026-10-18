extern unsigned char gTRKCPUState[];

unsigned int TRKTargetGetPC(void)
{
    return *(unsigned int *)(gTRKCPUState + 0x80);
}
