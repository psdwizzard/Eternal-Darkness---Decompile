typedef unsigned char u8;
typedef unsigned long u32;

extern u32 lbl_806513D4;
extern u32 lbl_8064CBA0;
extern int lbl_8064CBA4;

extern void fn_801ECB40(u8);
extern void fn_801A8660(int, int, int, int, int, u32*);

void fn_801F3158(int arg)
{
    volatile u32 value = lbl_806513D4;

    if (arg != 0) {
        u32 saved = lbl_8064CBA0;
        fn_801ECB40(0);
        if (lbl_8064CBA4 == 1) {
            u32 a = value;
            fn_801A8660(-83, 0, 806, 75, -1, &a);
            {
                u32 b = value;
                fn_801A8660(-83, 405, 806, 75, -1, &b);
            }
        } else {
            u32 a = value;
            fn_801A8660(0, 0, 640, 75, -1, &a);
            {
                u32 b = value;
                fn_801A8660(0, 405, 640, 75, -1, &b);
            }
        }
        fn_801ECB40((u8)saved);
    }
}
