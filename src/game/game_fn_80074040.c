extern void *fn_801A7498(void *);
extern void *fn_801A7490(void *);
extern unsigned long long fn_8020123C();

int fn_80074040(void *unused, void *argument)
{
    void *second;

    unused = fn_801A7498(argument);
    second = fn_801A7490(argument);
    fn_8020123C(0x72, unused, second, argument);
    return 1;
}
