typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Actor {
    u8 pad00[0x84];
    u16 flags;
} Actor;

typedef struct Runtime Runtime;
typedef struct Queue Queue;
typedef struct Object800A30F4 Object800A30F4;
typedef struct Object80201D2C Object80201D2C;
typedef struct Object80201D14 Object80201D14;

extern int fn_80201B54(int *object);
extern void *fn_800A1D28();
extern u8 *fn_801294DC(void *owner, int kind, int flags, int mode);
extern int fn_802045AC(void *object, Vec3 *position);
extern float fn_8012B7D0(const void *a, const void *b);
extern void fn_80129BA4(u8 *entry, float value, float scale);
extern void fn_801287C4(Queue *queue, void *callback, u32 value, u32 kind);
extern void fn_80128C28(Runtime *runtime, u32 callback, u32 argument);
extern void fn_80128C44(Runtime *runtime, u32 callback, u32 argument);
extern u8 fn_800A30F4(Object800A30F4 *object, u8 value);
extern void fn_80201D2C(Object80201D2C *object, int value);
extern void fn_80201D14(Object80201D14 *object, u8 value);
extern int fn_800A1A24(void *unused, void *object);
extern int fn_800A1A50(void *value, void *object);
extern int fn_80204810(void *object, int event);
extern float lbl_8064F348;

int fn_800D0328(void *object, void *target)
{
    Vec3 position;
    Vec3 position_copy;
    int result = 1;
    int object_id;
    u8 *entry;

    if (object != 0) {
        object_id = fn_80201B54((int *)object);
    } else {
        object_id = 0;
    }
    {
        Actor *actor = fn_800A1D28(object);
        actor->flags &= ~0x80;
        entry = fn_801294DC(target, 0x6F, 0x104, 6);
        if (entry != 0) {
            fn_802045AC(object, &position);
            position_copy = position;
            fn_80129BA4(entry, fn_8012B7D0(target, &position_copy), lbl_8064F348);
            fn_801287C4((Queue *)entry, (void *)fn_800A1A24, (u32)actor, 0x1E);
            fn_80128C28((Runtime *)entry, (u32)fn_80204810, (object_id << 8) | 0xC);
            fn_80128C44((Runtime *)entry, (u32)fn_800A1A50, (u32)object);
            fn_800A30F4((Object800A30F4 *)actor, 1);
            fn_80201D2C((Object80201D2C *)object, 0x44);
            fn_80201D14((Object80201D14 *)object, 1);
        } else {
            result = 0;
        }
    }
    return result;
}
