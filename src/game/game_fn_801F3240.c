typedef unsigned char u8;
typedef unsigned long u32;

extern int lbl_8064CBA4;
extern u32 lbl_8064CBA0;
extern u32 lbl_806513D8;
extern float lbl_80651348, lbl_8065134C, lbl_80651374, lbl_80651378;
extern float lbl_8065137C, lbl_806513DC, lbl_806513E0;

extern void fn_802119B0(float*, float, float, float, float, float, float);
extern void fn_8022B4B8(float*, int);
extern void fn_801ECB40(u8);
extern void fn_801A8660(int, int, int, int, int, u32*);

void fn_801F3240(void)
{
    volatile u32 value = lbl_806513D8;
    float projection[16];

    if (lbl_8064CBA4 == 1) {
        u32 saved = lbl_8064CBA0;
        fn_802119B0(projection, lbl_80651348, lbl_8065137C,
                    lbl_80651348, lbl_80651378, lbl_8065134C,
                    lbl_80651374);
        fn_8022B4B8(projection, 1);
        fn_801ECB40(0);
        {
            u32 a = value;
            fn_801A8660(0, 0, 83, 480, -1, &a);
        }
        {
            u32 b = value;
            fn_801A8660(557, 0, 83, 480, -1, &b);
        }
        fn_801ECB40((u8)saved);
        fn_802119B0(projection, lbl_80651348, lbl_8065137C,
                    lbl_806513DC, lbl_806513E0, lbl_8065134C,
                    lbl_80651374);
        fn_8022B4B8(projection, 1);
    } else {
        u32 saved = lbl_8064CBA0;
        fn_801ECB40(0);
        {
            u32 a = value;
            fn_801A8660(0, 0, 3, 480, -1, &a);
        }
        {
            u32 b = value;
            fn_801A8660(637, 0, 3, 480, -1, &b);
        }
        fn_801ECB40((u8)saved);
    }
}
