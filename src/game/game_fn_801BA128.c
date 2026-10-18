typedef unsigned char u8;
typedef unsigned int u32;

extern u32 synthFlags;

void CheckOutputMode(u8* first, u8* second)
{
    u32 flags = synthFlags;

    if (flags & 1) {
        *first = 0x40;
        *second = 0;
        return;
    }
    if (!(flags & 2)) {
        *second = 0;
    }
}
