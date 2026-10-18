extern volatile unsigned int gWritePos;
extern unsigned char gWriteBuf[];

int WriteUART1(unsigned char value)
{
    gWriteBuf[gWritePos++] = value;
    return 0;
}
