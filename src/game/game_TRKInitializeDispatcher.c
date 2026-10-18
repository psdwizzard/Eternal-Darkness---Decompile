extern unsigned int gTRKDispatchTableSize;

int TRKInitializeDispatcher(void)
{
    gTRKDispatchTableSize = 0x20;
    return 0;
}
