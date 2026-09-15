typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;

extern u16 lbl_80607120[];
extern unsigned int fn_800FBFB0(void);
extern void* memcpy(void*, const void*, unsigned int);

void fn_8018C8FC(u8* dest, const u8* color, int repeats, int run_length,
                 u16 offset, u8 bits)
{
    int mask = (1 << bits) - 1;
    int midpoint = 1 << (bits - 1);
    u8 repeat_count = repeats;
    int i;
    int j;
    u8* cursor = dest;

    for (i = 0; i < repeat_count; i++) {
        s8 delta = midpoint - (fn_800FBFB0() & mask);
        for (j = 0; j < run_length; j++) {
            cursor[0] = color[0] + delta;
            cursor[1] = color[1] + delta;
            cursor[2] = color[2] + delta;
            cursor[3] = color[3];
            cursor += 4;
        }
    }
    memcpy(dest + offset * 4, dest, lbl_80607120[6]);
}
