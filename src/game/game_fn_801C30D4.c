typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 adsrHandle(void* envelope, u16* level, u16* delta);

int adsrHandleLowPrecision(void* envelope, u16* level, u16* delta)
{
    u8 i;

    for (i = 0; i < 15; i++) {
        if (adsrHandle(envelope, level, delta) != 0) {
            return 1;
        }
    }
    return 0;
}
