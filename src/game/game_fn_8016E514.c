extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void fn_80163BB4(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_801F700C(int, void*);
extern const char lbl_8024FF00[];

int fn_8016E514(void* state)
{
    int value;
    void* target;
    if (fn_8016A598(state) != 1) {
        fn_80163BB4(state, lbl_8024FF00, 1, fn_8016A598(state));
        return 0;
    }
    value = (int)fn_8016A694(state, 1);
    fn_80201814(value);
    target = fn_80201BC8();
    fn_801F700C(2, target);
    return 1;
}
