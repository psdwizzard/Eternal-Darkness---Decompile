typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Object {
    u8 bytes[0x1000];
} Object;

extern void fn_801D8318(void);
extern void fn_801D0CA4(Object*);
extern Object* fn_801D0D78(int, u32, u32, void*, void (*)(void), u32, u32,
                           u32, u32, u32);
extern void* fn_801D38E8(u32);
extern void fn_801D38BC(void*, u32*, s16*);
extern u32 fn_801CEB2C(u32);
extern void fn_801CE594(u32, u32, void*, u32, u32, s16, u32, u32, void*,
                        u32, u32, u32, void (*)(Object*), Object*, u32*);

Object* fn_801D70B0(int resource, u32 flags, u32 subject, void* position,
                    u8 type, u32 value, u32 arg4, u32 arg5, u32 arg6,
                    u32 arg7)
{
    u32 first;
    s16 second;
    u32 copied;
    Object* object;

    object = fn_801D0D78(resource, flags, subject, position, fn_801D8318,
                         arg4, arg5, arg6, arg7, value);
    object->bytes[0xBC] = type;
    *(u32*)(object->bytes + 0xC0) = subject;
    *(u32*)(object->bytes + 0xC8) = 0;
    fn_801D38BC(fn_801D38E8(flags), &first, &second);
    copied = first;
    fn_801CE594(flags, subject, position, fn_801CEB2C(flags), 250, second,
                 22, 22, position, 180, 0, 600, fn_801D0CA4, object,
                 &copied);
    return object;
}
