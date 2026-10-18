typedef unsigned char u8;

extern void TRK_flush_cache(void *, unsigned int);

int TRKTargetFlushCache(u8 options, unsigned int start, unsigned int end)
{
    if (start < end) {
        TRK_flush_cache((void *)start, end - start);
        return 0;
    }
    return 0x700;
}
