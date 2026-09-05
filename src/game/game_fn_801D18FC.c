typedef unsigned int u32;
typedef signed short s16;

extern int lbl_8064D548;
extern void fn_801D2440(void);
extern void fn_801D0CA4(void);
extern void* fn_801D0D78(u32, u32, u32, void*, void (*)(void), u32, u32,
                         u32, u32, u32);
extern u32 fn_801D38E8(u32);
extern void fn_801D38BC(u32, u32*, s16*);
extern u32 fn_801CEB2C(u32);
extern void fn_801CE594(u32, u32, void*, u32, u32, u32, u32, u32,
                        void*, u32, u32, u32, u32, u32, u32*);

void* fn_801D18FC(u32 arg0, u32 id, u32 kind, u32 valueC4, void* position,
                  u32 arg5, u32 valueBC, u32 valueC0, u32 arg8, u32 arg9,
                  u32 arg10)
{
    u32 packed;
    s16 action;
    u32 copied;
    void* object;

    lbl_8064D548 = 1;
    object = fn_801D0D78(arg0, id, kind, position, fn_801D2440, valueC0,
                         arg8, arg9, arg10, arg5);
    *(u32*)((char*)object + 0xBC) = valueBC;
    *(u32*)((char*)object + 0xC4) = valueC4;
    fn_801D38BC(fn_801D38E8(id), &packed, &action);
    copied = packed;
    fn_801CE594(id, kind, position, fn_801CEB2C(id), 250, action, 100, 40,
                position, 70, 0, 450, (u32)fn_801D0CA4, (u32)object, &copied);
    return object;
}
