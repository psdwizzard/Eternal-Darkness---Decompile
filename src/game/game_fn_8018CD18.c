typedef unsigned char u8;
typedef unsigned short u16;

void fn_8018CD18(u16* dest, u8 count, u16 offset)
{
    u16* p = dest;
    int group;

    for (group = 0; group < 2; group++) {
        int i;
        for (i = 0; i < count; i++) {
            p[0] = 0x200;
            p[1] = 0;
            p[2] = 0;
            p[3] = 0;
            p[4] = 0;
            p[5] = 0x200;
            p[6] = 0x200;
            p[7] = 0x200;
            p += 8;
        }
        p = dest + offset * 2;
    }
}
