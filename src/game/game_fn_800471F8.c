extern int fn_80071258(void);
extern int fn_801A98F4(int index, void *object);

int fn_800471F8(void)
{
    int result = 1;

    if (fn_80071258() != 0) {
        result = 0;
        fn_801A98F4(0x67, (void *)0x64);
    }
    return result;
}
