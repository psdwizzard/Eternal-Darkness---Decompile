typedef unsigned int u32;

extern void* lbl_8064C4E4;
extern u32 lbl_8064D18C;
extern u32 lbl_8064C5F0;
extern u32 lbl_8064C5F4;
extern int lbl_8064C5D8;

extern int fn_8011EB04(void *);
#define fn_8011EB04(a) fn_8011EB04((void *)(a))
extern int fn_8011EB14(void*);
extern int fn_80128EAC(void*);
extern void fn_80157438(int, int);
extern void fn_800073D8(int);
extern void fn_801A6F94(void);
extern void fn_80204A8C(void);
extern void fn_8020525C(void);
extern void* fn_80201B3C();
extern void fn_80201C2C(void);
extern void fn_802007DC(void);
extern void fn_801AA9FC(int);
extern void fn_80006D50(int, int);

void fn_800068E0(void)
{
    fn_8011EB04(lbl_8064C4E4);
    fn_8011EB14(lbl_8064C4E4);
    fn_80128EAC(lbl_8064C4E4);
    fn_80157438(9, 0);
    fn_800073D8(-1);
    fn_801A6F94();
    fn_800073D8(lbl_8064D18C);
    fn_80204A8C();
    fn_8020525C();
    fn_80201B3C();
    fn_80201C2C();
    fn_8020525C();
    fn_802007DC();
    fn_801AA9FC(3);
}

void fn_80006954(u32 value)
{
    lbl_8064C5F0 = value > lbl_8064C5F0 ? value : lbl_8064C5F0;
}

u32 fn_8000696C(void)
{
    return lbl_8064C5F0;
}

void fn_80006974(int unused, int event)
{
    if (event == 1) {
        if (lbl_8064C5F4 != 0) {
            lbl_8064C5F4--;
        }
        if (lbl_8064C5F0 != 0) {
            lbl_8064C5F0--;
        } else if (lbl_8064C5D8 != 0) {
            fn_80006D50(0, 1);
        }
    }
}
