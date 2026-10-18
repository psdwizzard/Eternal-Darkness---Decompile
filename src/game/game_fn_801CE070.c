typedef unsigned char u8;

extern u8 salAIBufferIndex;
extern u8* salAIBufferBase;

void* salAiGetDest(void)
{
    return salAIBufferBase + (u8)((salAIBufferIndex + 2) % 4) * 0x280;
}
