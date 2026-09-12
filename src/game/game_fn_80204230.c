extern int fn_801A7540(int object);
extern int fn_801A7498(int object);
extern void fn_801A7228(int object);
extern void fn_8020123C(int first, int second, int third, int value);

int fn_80204230(int unused, int object)
{
    if (object != 0) {
        int first = fn_801A7540(object);
        int second = fn_801A7498(object);
        if (first != 0) {
            fn_8020123C(first, second, second, 0);
        }
        fn_801A7228(object);
    }
    return 1;
}
