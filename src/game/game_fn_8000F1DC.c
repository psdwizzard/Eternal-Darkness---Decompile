typedef signed short s16;
typedef unsigned int u32;
typedef int s32;

#pragma use_lmw_stmw on

typedef struct ObjectData {
    unsigned char pad0[0x152];
    s16 x;
    s16 y;
    s16 value;
} ObjectData;

typedef struct Object {
    unsigned char pad0[0x8C];
    ObjectData* data;
} Object;

extern int fn_8016A598(void*);
extern double fn_8016A694(void*, int);
extern void *fn_80201814();
extern void *fn_80201B8C();
extern void fn_80201ADC(Object*);
extern void fn_800CAC5C(s32, s32, s32*, s32*, s32*);
extern unsigned int fn_80036D5C(void*);
extern void fn_80036DA4(void*, u32);

s32 fn_8000F1DC(void* script)
{
    void* script_reg;
    s32 arg2;
    s32 arg1;
    s32 arg4;
    s32 arg3;
    s32 arg_count;
    void* entity;
    Object* object;
    ObjectData* data;
    s32 unused;
    s32 x;
    s32 y;
    u32 flags;

    script_reg = script;
    arg4 = 0;
    arg_count = fn_8016A598(script_reg);
    arg3 = 0;
    switch (arg_count) {
    case 2:
        arg1 = (s32)fn_8016A694(script_reg, 1);
        arg2 = (s32)fn_8016A694(script_reg, 2);
        break;
    case 3:
        arg1 = (s32)fn_8016A694(script_reg, 1);
        arg2 = (s32)fn_8016A694(script_reg, 2);
        arg3 = (s32)fn_8016A694(script_reg, 3);
        break;
    case 4:
        arg1 = (s32)fn_8016A694(script_reg, 1);
        arg2 = (s32)fn_8016A694(script_reg, 2);
        arg3 = (s32)fn_8016A694(script_reg, 3);
        arg4 = (s32)fn_8016A694(script_reg, 4);
        break;
    }

    entity = fn_80201814(arg1);
    if (entity != 0) {
        object = fn_80201B8C(entity);
        data = object->data;
        fn_80201ADC(object);
        fn_800CAC5C(5, arg2, &x, &y, &unused);
        data->x = x;
        data->y = y;
        data->value = arg4;
        flags = fn_80036D5C(entity);
        if (arg3 == 0) {
            flags = (flags | 0x80) & ~0x8000;
        } else {
            flags = (flags | 0x8000) & ~0x80;
        }
        fn_80036DA4(entity, flags);
    }
    return 0;
}
