typedef unsigned short u16;
typedef unsigned int u32;

extern void* lbl_8064D6BC;
extern void* lbl_8064C4E4;
extern void* lbl_8064D6B8;
extern u32 lbl_80651F40;
extern unsigned char lbl_8030F540[];

extern void* fn_8011FCE4(void*);
extern void fn_80139940(int);
extern void fn_801387EC(void*);
extern void fn_801F5240(int);
extern void fn_801F3528(u32*);

void fn_801F550C(void)
{
    void* object;
    u32 event;

    if (lbl_8064D6BC == 0) {
        if (lbl_8064C4E4 != 0) object = fn_8011FCE4(lbl_8064C4E4);
        else object = 0;
        fn_80139940(1);
        fn_801387EC(object);
    }
    lbl_8064D6B8 = 0;
    fn_801F5240(0);
    event = lbl_80651F40;
    fn_801F3528(&event);
    *(u16*)(lbl_8030F540 + 470) = 0;
}
