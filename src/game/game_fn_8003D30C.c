typedef unsigned int u32;

extern unsigned char fn_80128EE4(void *);
extern u32 fn_801A7498(void *);
extern u32 fn_801A7490(void *);
extern void *fn_80201814(int);
extern int fn_8003BD48(void *, void *);
extern void *fn_801A717C(void);
extern void fn_8012B344(void *);
extern void fn_801A7470(void *, u32);
extern void fn_801A74A0(void *, u32);
extern void fn_801A74A8(void *, u32);
extern unsigned long long fn_8020123C(int, int, int, int);
extern void fn_801A7228(void *);

u32 fn_8003D30C(register unsigned char *object, register unsigned char *argument)
{
    register unsigned char *resolved;
    register void *saved_object;
    register u32 first;
    register u32 second;
    register void *event;
    register u32 result;
    register void *saved_argument;
    register unsigned char object_flags;

    saved_argument = argument;
    resolved = saved_argument;
    saved_object = object;
    result = 0;
    first = fn_801A7498(resolved);
    second = fn_801A7490(resolved);
    resolved = fn_80201814(first);
    fn_80201814(second);
    if (resolved != 0 && saved_object != 0) {
        result = fn_8003BD48(saved_object, saved_argument);
        object_flags = fn_80128EE4(saved_object);
        if ((result & 0x40) != 0 && (object_flags & 0x20) != 0) {
            event = fn_801A717C();
            fn_8012B344(saved_object);
            fn_801A7470(event, 0xB);
            fn_801A74A0(event, first);
            fn_801A74A8(event, first);
            fn_8020123C(0x35, first, first, (int)event);
            fn_801A7228(event);
        }
    }
    return result;
}
