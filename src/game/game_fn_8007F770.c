typedef int s32;
typedef unsigned int u32;

extern const char lbl_80244EDC[];
extern unsigned char lbl_8031CD84[];
extern s32 lbl_8064C8F0;

extern int fn_8016A598(void *);
extern void fn_80163BB4(void *, const char *, ...);
extern void fn_8016A830(void *, double);

s32 fn_8007F770(void *script)
{
    if (fn_8016A598(script) != 0) {
        fn_80163BB4(script, lbl_80244EDC, 0, fn_8016A598(script));
        return 0;
    }

    fn_8016A830(script, (double)((u32 *)(lbl_8031CD84 + 0x444))[lbl_8064C8F0 * 2]);
    return 1;
}
