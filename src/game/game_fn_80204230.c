extern int fn_801A7540(int object);
extern int fn_801A7498(int object);
extern void fn_801A7228(int object);
extern void fn_8020123C(int first, int second, int third, int value);

int fn_80204230(int unused, int object)
{
    int second;

    if (object != 0) {
        unused = fn_801A7540(object);
        second = fn_801A7498(object);
        if (unused != 0) {
            fn_8020123C(unused, second, second, 0);
        }
        fn_801A7228(object);
    }
    return 1;
}
