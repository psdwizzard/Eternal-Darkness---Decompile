typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct ObjectData {
    u8 pad[0x9F];
    u8 kind;
} ObjectData;

typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;

typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Owner {
    u8 pad00[0x20];
    u8 collection[0x80];
    u8 object[0x44];
    void *shapes;
} Owner;
typedef struct Entry80201814 {
    struct Entry80201814 *prev;
    struct Entry80201814 *next;
    int unk8;
    int unkC;
    int id;
} Entry80201814;

/* Each setter exposes a different view of the event record. */
typedef struct { u8 pad[0x9C]; u32 value; } EventSource;
typedef struct { u8 pad[0x98]; u32 value; } EventTarget;
typedef struct { u8 pad[0xB6]; unsigned short value; } EventType;
typedef struct { u8 pad[0xB4]; signed short value; } EventParameter;
typedef struct { u8 pad[0x88]; u32 value; } EventHandle;
typedef struct { u32 words[3]; } Value;
typedef struct { u8 pad[0x54]; Value value; } EventPosition;

extern int fn_80201B44(void);
extern int fn_80201B54(int *object);
extern Entry80201814 *fn_80201814(int id);
extern void *fn_80201BC8(void *object);
extern void *fn_80201B8C(u8 *object);
extern void fn_8011F114(Vec3 *destination, Vec3 *source);
extern void *fn_80036D5C(void *object);
extern int fn_80204434(void *object, Vec3 *position, float *delta_out, float tolerance);
extern void *fn_8012AB2C(u8 *owner);
extern float fn_8011F6F8(void *object);
extern void fn_8013F3C0(Shape *out, const Vec3 *first, const Vec3 *second, float radius);
extern void *fn_8013FBE4(Owner *owner, const void *value, Result *out, void *context, unsigned int flags);
extern void *fn_801A717C(void);
extern void fn_801A74A0(EventSource *data, u32 value);
extern void fn_801A74A8(EventTarget *data, u32 value);
extern void fn_801A7538(EventType *data, unsigned short value);
extern void fn_801A7518(EventParameter *data, signed short value);
extern void fn_801A7470(EventHandle *data, u32 value);
extern void fn_801A764C(EventPosition *data, const Value *value);
extern void fn_8020104C(int, int, int, int, float);
extern void fn_80036DA4(void *object, void *value);
extern void fn_801A977C(void *object, int kind);
extern float lbl_8064F29C;
extern double lbl_8064F2F8;
extern float lbl_8064F300;
extern float lbl_8064F304;

s32 fn_800CC650(void *object, u32 flags, s32 mode, signed short param3)
{
    Shape shape;
    Result result;
    Vec3 second_pos;
    Vec3 first_pos;
    s32 actor;
    s32 object_id;
    Entry80201814 *actor_entry;
    void *object_transform;
    void *actor_object;
    void *sound;
    Owner *candidate;

    actor = fn_80201B44();
    object_id = fn_80201B54(object);
    actor_entry = fn_80201814(actor);
    actor_object = fn_80201BC8(actor_entry);
    object_transform = fn_80201BC8(object);
    if (((ObjectData *)fn_80201B8C((u8 *)actor_entry))->kind != 1)
        return 0;
    if (actor_object != 0)
        fn_8011F114(&first_pos, actor_object);
    if (actor_entry != 0 && (flags & (u32)fn_80036D5C(object)) == 0 &&
        actor_object != 0 && object_transform != 0 &&
        (u8)fn_80204434(object_transform, &first_pos, 0, lbl_8064F300) != 0) {
        candidate = fn_8012AB2C(object_transform);
        fn_8011F114(&second_pos, object_transform);
        {
            double delta = lbl_8064F2F8 + fn_8011F6F8(object_transform);
            second_pos.z = (float)((double)second_pos.z + delta);
        }
        {
            double delta = lbl_8064F2F8 + fn_8011F6F8(object_transform);
            first_pos.z = (float)((double)first_pos.z + delta);
        }
        fn_8013F3C0(&shape, &second_pos, &first_pos, lbl_8064F304);
        if (fn_8013FBE4(candidate, &shape, &result, 0, 8) == 0) {
            sound = fn_801A717C();
            fn_801A74A0(sound, object_id);
            fn_801A74A8(sound, actor);
            fn_801A7538(sound, 2);
            fn_801A7518(sound, param3);
            fn_801A7470(sound, -1);
            fn_801A764C(sound, (const Value *)&second_pos);
            fn_8020104C(0x3A, object_id, actor, (s32)sound, lbl_8064F29C);
            fn_80036DA4(object, (void *)(flags | (u32)fn_80036D5C(object)));
            if (mode != -1)
                fn_801A977C(object_transform, 0x17);
            return 1;
        }
    }
    return 0;
}
