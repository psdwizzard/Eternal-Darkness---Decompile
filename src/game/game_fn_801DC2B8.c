typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

typedef struct Payload {
    u32 words[30];
} Payload;

typedef struct Object {
    u8 pad00[8];
    u32 field_08;
    u8 pad0C[0x38];
    Payload payload;
    u16 start_x;
    u16 start_y;
    u16 start_z;
    u16 end_x;
    u16 end_y;
    u16 end_z;
    u16 field_C8;
    u8 padCA[2];
    void* effects[969];
    u8 flags;
    u8 state;
    u8 active;
} Object;

extern const f32 lbl_806511A0;
extern void fn_801DC778(void);
extern Object* fn_801D0D78(u32, u32, u32, Vec3*, void (*)(void), u32, u32,
                           u32, u32, u32);
extern void fn_801D0CA4(Object*);
extern void fn_801CE384(u32, Vec3*, u16, u32, u8, void**);
extern void* memset(void*, int, u32);

void fn_801DC2B8(u32 owner, u32 type, u32 kind, Vec3* position,
                 Payload* payload)
{
    f32 height;
    Object* object = fn_801D0D78(0, type, kind, position, fn_801DC778,
                                  0, 0, 0, 0, 0);
    object->state = 4;
    object->field_08 = owner;
    fn_801D0CA4(object);
    object->active = 4;
    if (payload != 0) {
        object->payload = *payload;
    } else {
        memset(&object->payload, 0, sizeof(Payload));
    }
    fn_801CE384(type, position, 0, 1, 0, object->effects);
    height = lbl_806511A0;
    object->start_x = position->x;
    object->start_y = position->y;
    object->start_z = position->z;
    object->end_x = position->x;
    object->end_y = position->y;
    object->end_z = height + position->z;
    object->field_C8 = 0;
}
