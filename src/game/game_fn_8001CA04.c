typedef unsigned int u32;
typedef int s32;

extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_8016A7D8(void*);
extern void fn_8016A830(void*, double);
extern void fn_80163BB4(void*, const char*, ...);
extern u32 fn_8004519C(void);
extern s32 fn_800451E4(s32);
char lbl_8023CD70[] = "\nInvalid Alignment of %i\n";
char lbl_8023CD8C[] =
    "\nInvalid Num of Args Expecting 0 or 1, and got %i\n";
extern double lbl_8064DE60;
extern double lbl_8064DCF8;

s32 fn_8001CA04(void* script)
{
    s32 mode;
    switch (fn_8016A598(script)) {
    case 0:
        fn_8016A830(script, (double)fn_8004519C());
        break;
    case 1:
        mode = (s32)fn_8016A694(script, 1);
        switch (mode) {
        case 1:
        case 2:
        case 3:
            if (fn_800451E4(mode) != 0) {
                fn_8016A830(script, lbl_8064DCF8);
            } else {
                fn_8016A7D8(script);
            }
            break;
        default:
            fn_80163BB4(script, lbl_8023CD70, mode);
            return 0;
        }
        break;
    default:
        fn_80163BB4(script, lbl_8023CD8C, fn_8016A598(script));
        return 0;
    }
    return 1;
}
