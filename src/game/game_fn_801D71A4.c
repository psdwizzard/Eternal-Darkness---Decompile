typedef unsigned char u8;
typedef unsigned int u32;
typedef float f32;

typedef struct Object {
    u8 pad00[8];
    u32 owner;
    u8 pad0C[0xB0];
    u32 valueBC;
    u32 valueC0;
    u32 valueC4;
    u8 clearC8[0x1C];
    u32 valueE4;
    u8 paramsE8[0x1C];
    f32 value104;
    u8 pad108[4];
    u32 value10C;
    u8 clear110[0x2A];
    u8 type13A;
    u8 pad13B[0xEB6];
    u8 stateFF1;
    u8 kindFF2;
} Object;

extern void* memset(void*, int, u32);
extern void fn_801D84F4(void);
extern Object* fn_801D0D78(u32, u32, u32, void*, void (*)(void), u32, u32,
                           u32, u32, u32);
extern void fn_801D0CA4(Object*);
extern void fn_801CE720(u32, u32, void*, u32, u32, u32, void*, f32);

Object* fn_801D71A4(u32 flags, void* position, u32 arg2, u8 type,
                    void** first, void** second, u32 owner, f32 value,
                    void** third)
{
    Object* object;

    object = fn_801D0D78(0, flags, arg2, position, fn_801D84F4, 0, 0, 0, 0, 0);
    object->stateFF1 = 5;
    object->owner = owner;
    fn_801D0CA4(object);
    object->kindFF2 = 4;
    object->valueBC = arg2;
    object->valueC4 = 0;
    memset(object->clearC8, 0, sizeof(object->clearC8));
    memset(object->clear110, 0, sizeof(object->clear110));
    object->type13A = type;
    object->valueE4 = 1;
    object->value10C = 0;
    object->value104 = value;
    fn_801CE720(flags, owner, position, 0, 1, 0, object->paramsE8, value);
    *first = &object->valueE4;
    *second = &object->valueC0;
    if (third != 0) {
        *third = &object->value10C;
    }
    return object;
}
