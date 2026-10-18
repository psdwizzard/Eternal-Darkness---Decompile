typedef unsigned char u8;
typedef signed short s16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3 {
    u32 x;
    u32 y;
    u32 z;
} Vec3;

typedef struct Object Object;
struct Object {
    u8 pad0[4];
    s32 timer;
    u8 pad8[4];
    s32 timer_copy;
    s32 random_value;
    u8 pad14[8];
    Vec3 position;
    s32 value;
    s16 kind;
    u8 pad2e[2];
    s16 duration;
    u8 pad32[2];
    s16 field34;
    u8 byte36;
    u8 pad37;
    u8 byte38;
    u8 pad39[0xF];
    void (*callback)(Object*);
    u8 pad4c[0x24];
    s32 enabled;
};

extern s32 lbl_8064D18C;

extern u32 rand(void);
extern void fn_801FE8DC(s32*, f32, f32, f32);
extern void fn_801E8328(s32, Object*);
extern void fn_801E2BF8(Object*);

void fn_801E2B28(Object* object, Vec3* position, s32* value, s16 kind, u8 byte36)
{
    object->field34 = lbl_8064D18C;
    object->timer = 100000;
    object->timer_copy = object->timer;
    object->random_value = (rand() & 0xF) + 1;
    object->position = *position;
    object->value = *value;
    object->callback = fn_801E2BF8;
    object->kind = kind;
    object->byte36 = byte36;
    object->duration = 600;
    object->enabled = 1;
    object->byte38 = 4;
    fn_801FE8DC(&object->timer, 0.0f, 0.0f, 1.5f);
    fn_801E8328(0x13, object);
}
