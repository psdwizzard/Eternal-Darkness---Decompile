extern int fn_801DA27C(int);
extern void fn_8020123C(int, int, int, int);

void fn_801DA890(int value)
{
    int object = fn_801DA27C(value);

    if (object != 0) {
        fn_8020123C(0x39, object, object, 0);
    }
}
