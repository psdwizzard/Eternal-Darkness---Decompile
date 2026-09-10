extern int fn_8016A598(void*);
extern void fn_80163BB4(void*, const char*, ...);
extern double fn_8016A694(void*, int);
extern void *fn_80201814();
extern void* fn_80204A8C(void);
extern void fn_80204CE4(void*, void*);
extern int fn_80201C2C(void*);
extern int fn_80204C2C(void*);
extern void* fn_80155DB4(void*);
extern void fn_801568B8(void*, int);
extern const char lbl_8024FF00[];

int fn_8016CEF0(void* state)
{
    void* result;
    void* source;
    void* target;
    void* handle;
    int third;
    int second;
    int first;

    if (fn_8016A598(state) != 3) {
        fn_80163BB4(state, lbl_8024FF00, 3, fn_8016A598(state));
        return 0;
    }

    first = (int)fn_8016A694(state, 1);
    second = (int)fn_8016A694(state, 2);
    third = (int)fn_8016A694(state, 3);

    if (first == -2) {
        target = fn_80201814(second);
        if (target != 0) {
            result = fn_80204A8C();
            fn_80204CE4(target, result);
        }
    } else {
        source = fn_80201814(first);
        if (source != 0) {
            target = fn_80201814(second);
            if (target != 0) {
                int value = fn_80201C2C(source);
                if (value == 0) {
                    value = fn_80204C2C(source);
                }
                fn_80204CE4(target, (void*)value);
                if (third == 0) {
                    handle = fn_80155DB4(target);
                    if (handle != 0) {
                        fn_801568B8(handle, 0);
                    }
                }
            }
        }
    }
    return 0;
}
