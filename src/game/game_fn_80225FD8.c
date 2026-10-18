/* GXInvalidateVtxCache: send the vertex cache invalidation command. */
typedef unsigned char u8;

void GXInvalidateVtxCache(void)
{
    *(volatile u8 *)0xCC008000 = 0x48;
}
