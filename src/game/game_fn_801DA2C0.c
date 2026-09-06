typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

extern void fn_801DADDC(void);
extern void fn_801D0CA4(void*);
extern void* fn_801D0D78(u32, u32, u32, void*, void (*)(void), u32, u32,
                         u32, u32, u32);
extern u32 fn_801D38E8(u32);
extern void fn_801D38BC(u32, u32*, s16*);
extern u32 fn_801CEB2C(u32);
extern void fn_801CE594(u32, u32, void*, u32, u32, s16, u32, u32, void*,
                        u32, u32, u32, void (*)(void*), void*, u32*);

void* fn_801DA2C0(u32 resource, u32 flags, u32 subject, void* position,
                  u8 type, u32 value, u32 arg6, u32 arg7, u32 arg8,
                  u32 arg9)
{
    u32 packed;
    s16 action;
    u32 copied;
    void* object;

    object = fn_801D0D78(resource, flags, subject, position, fn_801DADDC,
                         arg6, arg7, arg8, arg9, value);
    *(u32*)((u8*)object + 0xBC) = subject;
    *(u8*)((u8*)object + 0xC4) = type;
    fn_801D38BC(fn_801D38E8(flags), &packed, &action);
    copied = packed;
    fn_801CE594(flags, subject, position, fn_801CEB2C(flags), 250, action,
                 140, 10, position, 150, 0, 600, fn_801D0CA4, object,
                 &copied);
    return object;
}
