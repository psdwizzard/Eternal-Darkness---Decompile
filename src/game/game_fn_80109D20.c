extern void* lbl_8064CCA0;
extern int fn_801E8D34(void*);
extern void fn_801E8B24(void*, int, int);
extern int fn_801A98F4(int, int);
extern void fn_80144C40(void);

enum Mode {
    MODE_0,
    MODE_1,
    MODE_2,
    MODE_3
};

void fn_80109D20(short arg)
{
    int old = fn_801E8D34(lbl_8064CCA0);
    fn_801E8B24(lbl_8064CCA0, arg < 0 ? MODE_1 : MODE_2, 0);
    if (old != fn_801E8D34(lbl_8064CCA0)) {
        fn_801A98F4(0x221, 0x32);
    }
    fn_80144C40();
}
