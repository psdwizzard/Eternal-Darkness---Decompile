typedef unsigned int u32;

extern u32 __ARQChunkSize;

u32 ARQGetChunkSize(void)
{
    return __ARQChunkSize;
}
