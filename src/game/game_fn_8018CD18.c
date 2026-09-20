typedef unsigned char u8;
typedef unsigned short u16;

#define CURRENT_ENTRY(address) ((u16*)(address))

void fn_8018CD18(u16* dest, u8 count, u16 offset)
{
    unsigned long dest_r = (unsigned long)dest;
    u16* second;
    int group;

    second = (u16*)dest_r + offset * 2;
    for (group = 0; group < 2; group++) {
        int i;
        for (i = 0; i < count; i++) {
            CURRENT_ENTRY(dest_r)[0] = 0x200;
            CURRENT_ENTRY(dest_r)[1] = 0;
            CURRENT_ENTRY(dest_r)[2] = 0;
            CURRENT_ENTRY(dest_r)[3] = 0;
            CURRENT_ENTRY(dest_r)[4] = 0;
            CURRENT_ENTRY(dest_r)[5] = 0x200;
            CURRENT_ENTRY(dest_r)[6] = 0x200;
            CURRENT_ENTRY(dest_r)[7] = 0x200;
            dest_r += 8 * sizeof(u16);
        }
        dest_r = (unsigned long)second;
    }
}

#undef CURRENT_ENTRY
