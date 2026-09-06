typedef unsigned char u8;
typedef unsigned short u16;

extern u16 lbl_80607120[];
extern unsigned int fn_800FBFB0(void);
extern void* memcpy(void*, const void*, unsigned int);

void fn_8018C6EC(u8* dest, const u8* color, u8 repeats, int run_length, u16 offset)
{
    int i;
    int j;
    u8* cursor = dest;

    for (i = 0; i < repeats; i++) {
        for (j = 0; j < run_length; j++) {
            cursor[0] = color[0];
            cursor[1] = color[1];
            cursor[2] = color[2] - (fn_800FBFB0() & 0x1F);
            cursor[3] = color[3];
            cursor += 4;
        }
    }
    memcpy(dest + offset * 4, dest, lbl_80607120[6]);
}
