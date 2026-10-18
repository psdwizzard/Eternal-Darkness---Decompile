typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Color {
    u8 r, g, b, a;
} Color;

typedef struct ObjectData {
    u8 pad00[0x54];
    struct Slots *slots;
    u8 pad58[0x94 - 0x58];
    s32 object_id;
    u8 pad98[0x9F - 0x98];
    u8 kind;
} ObjectData;

typedef struct Slots {
    u8 pad00[0xC0];
    s32 handles[8];
    u8 padE0[0xFC - 0xE0];
    void *effect;
} Slots;

extern s32 lbl_8064D18C;
extern const float lbl_8064ED48;

/* Opaque object views used by the individual accessors. */
typedef struct Entry80201814 Entry80201814;
typedef struct Object Object;
typedef struct Object80201D44 Object80201D44;
typedef struct Object802015A4 Object802015A4;
typedef struct Object80201D34 Object80201D34;
typedef struct Object80201D1C Object80201D1C;
typedef struct State8009C870 State8009C870;

extern void *fn_80201BC8(void *);
extern s32 fn_80201B54(s32 *);
extern void *fn_80201B8C(u8 *);
extern void *fn_8011F130(void *);
extern void fn_801D0CF0(Object *);
extern void *fn_80201890(s32);
extern Entry80201814 *fn_80201814(s32);
extern u16 fn_8012DBE8(u8 *, u32, u8 *);
extern u32 rand(void);
extern void *fn_801D62D0(u32 first_id, void *first_a, void *first_b,
                        u32 second_id, void *second_a, void *second_b,
                        int type, int spawn_first, int spawn_third,
                        u8 spawn_second, u8 main14, u8 main15,
                        u8 child14, u8 child15, int set_4000, int set_8000,
                        u8 child17, u8 main18, u8 child18, u8 main19,
                        u8 main16, int enable, u16 value06, u32 flags,
                        u32 child_flags, u8 kind);
extern int fn_801AAE68(u16 id, u8 arg4, u8 arg5, float magnitude,
                       Vec3 *position, signed char active, u8 arg8, u8 arg9,
                       u16 kind, u32 flags);
extern void fn_8006A478(s32);
extern s32 fn_80201B5C(s32 *);
extern int fn_800CAC5C(int, int, int *, int *, int *);
extern u64 fn_8020123C(int, int, int, int);
extern void fn_80201D44(Object80201D44 *, int);
extern void fn_802015A4(Object802015A4 *);
extern void fn_80201D34(Object80201D34 *, int);
extern void fn_80201D1C(Object80201D1C *, u8);
extern int fn_801E8328(u32, u32);
extern int fn_8009C870(State8009C870 *, int);

void fn_8009C550(void *object)
{
    void *model;
    ObjectData *data;
    s32 owner;
    s32 handle;
    Vec3 *position;
    Slots *slots;
    u32 i;
    Entry80201814 *child;
    s32 release;
    u8 *runtime;
    ObjectData *childData;
    s32 a, b, c;
    Color color;

    model = fn_80201BC8(object);
    owner = fn_80201B54(object);
    data = fn_80201B8C(object);
    position = fn_8011F130(model);
    slots = data->slots;
    if (slots->effect != 0) {
        fn_801D0CF0(slots->effect);
        slots->effect = 0;
    }

    i = 0;
    do {
        handle = slots->handles[i];
        release = 0;
        if (handle > 0) {
            runtime = fn_80201890(handle);
            child = fn_80201814(handle);
            childData = fn_80201B8C((u8 *)child);
            fn_8012DBE8(runtime, 15, (u8 *)&color);
            if (color.a >= 0x20) {
                fn_801D62D0(owner, 0, (void *)1, handle, 0, (void *)1, data->object_id, 0,
                            0, rand() & 4, 0x10, 8, 3, 5, 0, 1, 0x11, 8,
                            4, 0x20, 0, 0, 0x3C, 0x42040, 0x2030, 4);
                fn_801AAE68(0xBE, 100, 0, lbl_8064ED48, position, 2, 2, 0,
                            lbl_8064D18C, 0);
            }
            if (childData->kind == 3 && childData->object_id == 2) {
                fn_8006A478((s32)child);
            }
            if (fn_80201B5C((s32 *)child) == 0x28) {
                if (color.a <= 0x80) {
                    release = 1;
                } else {
                    fn_800CAC5C(childData->kind, 1, &a, &b, &c);
                    fn_8020123C(0xF0, owner, handle, c);
                }
            } else if (fn_80201B5C((s32 *)child) == 0) {
                if (color.a <= 0x80) {
                    release = 1;
                } else {
                    fn_800CAC5C(childData->kind, 1, &a, &b, &c);
                    fn_80201D44((Object80201D44 *)child, c);
                    fn_802015A4((Object802015A4 *)child);
                }
            }
            if (release) {
                fn_80201D34((Object80201D34 *)child, 0);
                fn_80201D1C((Object80201D1C *)child, 1);
                fn_801E8328(2, (u32)child);
            } else {
                fn_8020123C(8, owner, handle, 0);
            }
            fn_8009C870((State8009C870 *)slots, handle);
        }
        i++;
    } while (i < 8);
}
