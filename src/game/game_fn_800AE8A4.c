typedef unsigned char u8;
typedef unsigned short u16;

extern int lbl_8064D5A8;
extern unsigned int rand(void);
extern int fn_800AE380(u16, unsigned int, void*, u16, u16, u16, u8, u16);

void fn_800AE8A4(u8 kind)
{
    if (kind != 0 && kind <= 2 && (lbl_8064D5A8 & 0x3F) == 0) {
        u16 duration = rand() & 0x7F;
        duration += 1800;
        fn_800AE380(0xFFFF, 1, 0, duration,
                   320, 2, kind, 0);
        if (kind == 2) {
            duration = rand() & 0x7F;
            duration += 5400;
            fn_800AE380(0xFFFF, 0, 0, duration,
                       320, 10, 2, 0);
        }
    }
}
