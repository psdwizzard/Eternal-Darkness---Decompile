typedef unsigned char u8;

extern void *fn_80201B8C();
extern int fn_80201B54();
extern unsigned long long fn_8020123C();

int fn_800777B0(void *unused, void *object)
{
    register unsigned long object_r = (unsigned long)object;
    register u8 *info;
    void *handle;

    info = *(u8 **)((u8 *)fn_80201B8C((void *)object_r) + 0x8C);
    handle = (void *)fn_80201B54((void *)object_r);

    fn_8020123C(0x6E, handle, *(void **)(info + 0x48), 0);
    return 1;
}
