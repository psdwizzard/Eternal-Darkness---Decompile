typedef unsigned char u8;
typedef unsigned short u16;

void fn_8018CB70(u16* dest, u8 count, u16 offset)
{
    u16* second = dest + offset * 2;
    u8 length = count;
    int group;

    for (group = 0; group < 2; group++) {
        int i;
        for (i = 0; i < length; i++) {
            dest[0] = 0x200;
            dest[1] = 0x200;
            dest[2] = 0;
            dest[3] = 0x200;
            dest[4] = 0;
            dest[5] = 0;
            dest[6] = 0x200;
            dest[7] = 0;
            dest += 8;
        }
        dest = second;
    }
}
