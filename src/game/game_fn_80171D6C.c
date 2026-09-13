extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern void fn_801AC5E4(int, unsigned char, unsigned char, int, signed char, int, int);
extern const char lbl_8024FF00[];

int fn_80171D6C(void* state)
{
    const char* strings = lbl_8024FF00;
    int arg1;
    int arg2;
    unsigned char clamped2;
    int arg3;
    int arg4;
    unsigned char clamped1;
    signed char clamped4;

    if (fn_8016A598(state) != 4) {
        fn_80163BB4(state, strings, 4, fn_8016A598(state));
        return 0;
    }
    arg1 = (int)fn_8016A694(state, 1);
    arg2 = (int)fn_8016A694(state, 2);
    arg3 = (int)fn_8016A694(state, 3);
    arg4 = (int)fn_8016A694(state, 4);
    clamped2 = (arg2 > 0 ? arg2 : 0) > 0x7F ? 0x7F : (arg2 > 0 ? arg2 : 0);
    if (arg2 != clamped2)
        fn_80163BB4(state, strings + 0x3A8, arg2, 0x7F);
    clamped4 = (arg4 > 0 ? arg4 : 0) > 0x7F ? 0x7F : (arg4 > 0 ? arg4 : 0);
    if (arg4 != clamped4)
        fn_80163BB4(state, strings + 0x40C, arg4);
    clamped1 = (arg1 > 0 ? arg1 : 0) > 0xFF ? 0xFF : (arg1 > 0 ? arg1 : 0);
    if (arg1 != clamped1)
        fn_80163BB4(state, strings + 0x434, arg4);
    fn_801AC5E4(0, clamped1, clamped2, arg3, clamped4, 0, 0);
    return 0;
}
