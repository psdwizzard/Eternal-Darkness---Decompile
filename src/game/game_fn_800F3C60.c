extern unsigned char gTRKState[];

int TRKTargetStop(void)
{
    *(int *)(gTRKState + 0x98) = 1;
    return 0;
}
