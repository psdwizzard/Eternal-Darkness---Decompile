extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern void fn_801AC5E4(unsigned short, int, unsigned char, int, signed char, int, int);
extern const char lbl_8024FF00[];

int fn_80171BB4(void* state)
{
    int arg4;
    int arg2;
    unsigned char clamped3;
    int arg5;
    signed char clamped5;
    struct {
        int arg1;
        int arg3;
        const char* strings;
    } args;
    args.strings = lbl_8024FF00;

    if (fn_8016A598(state) != 5) {
        fn_80163BB4(state, args.strings, 5, fn_8016A598(state));
        return 0;
    }

    args.arg1 = (int)fn_8016A694(state, 1);
    arg2 = (int)fn_8016A694(state, 2);
    args.arg3 = (int)fn_8016A694(state, 3);
    arg4 = (int)fn_8016A694(state, 4);
    arg5 = (int)fn_8016A694(state, 5);

    clamped3 = (args.arg3 > 0 ? args.arg3 : 0) > 0x7F
                   ? 0x7F
                   : (args.arg3 > 0 ? args.arg3 : 0);
    if (args.arg3 != clamped3) {
        fn_80163BB4(state, args.strings + 0x3A8, args.arg3, 0x7F);
    }

    clamped5 = (arg5 > 0 ? arg5 : 0) > 0xFF
                   ? 0xFF
                   : (arg5 > 0 ? arg5 : 0);
    if (arg5 != clamped5) {
        fn_80163BB4(state, args.strings + 0x3CC, arg5);
    }

    if (arg2 != 1 && arg2 != 2) {
        fn_80163BB4(state, args.strings + 0x3F4, arg2);
    }

    fn_801AC5E4((unsigned short)args.arg1, 0, clamped3, arg4, clamped5, arg2, 0);
    return 0;
}
