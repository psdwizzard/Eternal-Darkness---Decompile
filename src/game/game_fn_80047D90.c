typedef signed int s32;
typedef unsigned int u32;

extern u32 lbl_8030F4C0[];

extern int fn_801FE25C(u32 id);
extern void fn_801FDF74(u32 id, s32 value);
extern void fn_801FE4FC(u32 id);
extern void fn_8007BCD4(void);

void fn_80047D90(void)
{
    if (fn_801FE25C(lbl_8030F4C0[0]) != 0) {
        fn_801FDF74(lbl_8030F4C0[0], 0);
        fn_801FE4FC(lbl_8030F4C0[0]);
        fn_8007BCD4();
        lbl_8030F4C0[0] = 0;
    }
}
