typedef signed short s16;
typedef unsigned int u32;

extern void fn_801D9D14(void);
extern void fn_801D0CA4(void*);
extern void* fn_801D0D78(u32, u32, u32, void*, void (*)(void), u32, u32,
                         u32, u32, u32);
extern u32 fn_801D38E8(u32);
extern void fn_801D38BC(u32, u32*, s16*);
extern u32 fn_801CEB2C(u32);
extern void fn_801CE594(u32, u32, void*, u32, u32, s16, u32, u32, void*,
                        u32, u32, u32, void (*)(void*), void*, u32*);

void* fn_801D997C(u32 resource, u32 flags, u32 subject, void* position,
                  u32 value, u32 arg5, u32 arg6, u32 arg7, u32 arg8)
{
    u32 packed;
    s16 action;
    u32 copied;
    void* object;

    object = fn_801D0D78(resource, flags, subject, position, fn_801D9D14,
                         arg5, arg6, arg7, arg8, value);
    fn_801D38BC(fn_801D38E8(flags), &packed, &action);
    copied = packed;
    fn_801CE594(flags, subject, position, fn_801CEB2C(flags), 250, action,
                118, 10, position, 128, 0, 600, fn_801D0CA4, object,
                &copied);
    return object;
}
