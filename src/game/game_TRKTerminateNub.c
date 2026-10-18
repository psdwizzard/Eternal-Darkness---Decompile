extern void TRKTerminateSerialHandler(void);

int TRKTerminateNub(void)
{
    TRKTerminateSerialHandler();
    return 0;
}
