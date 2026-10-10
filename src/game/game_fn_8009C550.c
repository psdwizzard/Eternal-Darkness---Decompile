typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

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

extern void *fn_80201BC8(void *);
extern s32 fn_80201B54(void *);
extern void *fn_80201B8C();
extern Vec3 *fn_8011F130(void *);
extern void fn_801D0CF0(void *);
extern s32 fn_80201890(s32);
extern s32 fn_80201814(s32);
extern u16 fn_8012DBE8(s32, s32, Color *);
extern u32 fn_800FBFB0(void);
extern void fn_801D62D0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                       s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                       s32, s32, s32, s32, s32, s32);
extern void fn_801AAE68(s32, s32, s32, Vec3 *, s32, s32, s32, u16, float, s32);
extern void fn_8006A478(s32);
extern s32 fn_80201B5C(s32);
extern void fn_800CAC5C(u8, s32, s32 *, s32 *, s32 *);
extern void fn_8020123C(s32, s32, s32, s32);
extern void fn_80201D44(s32, s32);
extern void fn_802015A4(s32);
extern void fn_80201D34(s32, s32);
extern void fn_80201D1C(s32, s32);
extern void fn_801E8328(s32, s32);
extern void fn_8009C870(Slots *, s32);

void fn_8009C550(void *object)
{
    void *model;
    ObjectData *data;
    Slots *cursor;
    s32 owner;
    s32 handle;
    Vec3 *position;
    Slots *slots;
    u32 i;
    s32 child;
    s32 release;
    s32 runtime;
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

    cursor = slots;
    i = 0;
    do {
        handle = cursor->handles[0];
        release = 0;
        if (handle > 0) {
            runtime = fn_80201890(handle);
            child = fn_80201814(handle);
            childData = fn_80201B8C(child);
            fn_8012DBE8(runtime, 15, &color);
            if (color.a >= 0x20) {
                fn_801D62D0(owner, 0, 1, handle, 0, 1, data->object_id, 0,
                            0, fn_800FBFB0() & 4, 0x10, 8, 3, 5, 0, 1, 0x11, 8,
                            4, 0x20, 0, 0, 0x3C, 0x42040, 0x2030, 4);
                fn_801AAE68(0xBE, 100, 0, position, 2, 2, 0, lbl_8064D18C,
                            lbl_8064ED48, 0);
            }
            if (childData->kind == 3 && childData->object_id == 2) {
                fn_8006A478(child);
            }
            if (fn_80201B5C(child) == 0x28) {
                if (color.a <= 0x80) {
                    release = 1;
                } else {
                    fn_800CAC5C(childData->kind, 1, &a, &b, &c);
                    fn_8020123C(0xF0, owner, handle, c);
                }
            } else if (fn_80201B5C(child) == 0) {
                if (color.a <= 0x80) {
                    release = 1;
                } else {
                    fn_800CAC5C(childData->kind, 1, &a, &b, &c);
                    fn_80201D44(child, c);
                    fn_802015A4(child);
                }
            }
            if (release) {
                fn_80201D34(child, 0);
                fn_80201D1C(child, 1);
                fn_801E8328(2, child);
            } else {
                fn_8020123C(8, owner, handle, 0);
            }
            fn_8009C870(slots, handle);
        }
        i++;
        cursor = (Slots *)((s32 *)cursor + 1);
    } while (i < 8);
}
