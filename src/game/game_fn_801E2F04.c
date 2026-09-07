typedef signed short s16;
typedef unsigned int u32;

typedef struct Object {
    char pad0[0x38];
    u32 effect_position[3];
} Object;

extern void fn_801E3388(void);
extern void fn_801D0CA4(void*);
extern void* fn_80201814(u32);
extern Object* fn_801D0D78(u32, u32, u32, void*, void (*)(void), u32, u32,
                           u32, u32, u32);
extern u32 fn_801D38E8(u32);
extern void fn_801D38BC(u32, u32*, s16*);
extern u32 fn_801CEB2C(u32);
extern void fn_801CE594();

void* fn_801E2F04(u32 resource, u32 flags, u32 subject, void* position,
                  u32 value, u32 check, u32 arg6, u32 arg7, u32 arg8,
                  u32 arg9)
{
    u32 packed;
    s16 action;
    Object* object = 0;
    u32 copied;

    if (fn_80201814(check) != 0) {
        object = fn_801D0D78(resource, flags, subject, position, fn_801E3388,
                             arg6, arg7, arg8, arg9, value);
        *(u32*)((char*)object + 0xBC) = check;
        fn_801D38BC(fn_801D38E8(flags), &packed, &action);
        copied = packed;
        fn_801CE594(flags, subject, object->effect_position,
                     fn_801CEB2C(flags), 250, action, 200, 30,
                     object->effect_position, 210, 0, 600, fn_801D0CA4,
                     object, &copied);
    }
    return object;
}
