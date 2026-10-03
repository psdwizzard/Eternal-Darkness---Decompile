typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef signed char s8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct Effect {
    u8 pad00;
    u8 value01;
    u8 pad02;
    s8 value03;
    u16 value04;
    u16 value06;
    u16 value08;
    u8 pad0A[0xA];
    u8 value14;
    u8 pad15[3];
    u8 value18;
    u8 value19;
    u8 pad1A[2];
    u16 value1C;
    u8 pad1E[0x5A];
    u32 value78;
    u8 pad7C[0x14];
    void (*callback90)(void);
    void* object94;
    Vec3 position98;
    u8 descriptorA4[6];
    u8 valueAA;
} Effect;

typedef struct Work {
    u8 emitter[0xB0];
    Effect effect;
} Work;

typedef struct GameObject GameObject;

struct GameObject {
    u8 pad00[4];
    u32 owner;
    s32 type;
    s32 id;
    s32 handle;
    u8 pad14[0x14];
    void (*callback)(GameObject*, u32);
    u32 callback_arg;
    u8 pad30[8];
    Vec3 position;
    void* resource;
    u8 pad48[0x74];
    Work work;
    u8 pad218[0xDD8];
    u8 flags;
    u8 padFF1[3];
    u16 state;
};

typedef struct LookupRow {
    s16 values[5];
} LookupRow;

typedef struct Current {
    u8 pad0[0x3C];
    s32 value;
} Current;

typedef struct Context {
    u8 pad0[0x8C];
    Current* current;
} Context;

extern s32 lbl_8064D18C;
extern u32 lbl_8064C4E0;
extern u32* lbl_8064C5A8;
extern u32 lbl_80651F38;
extern u16 lbl_80651F3C;
extern Color lbl_802FC5BC[];
extern LookupRow lbl_8023BA30[];

extern void fn_801E237C(GameObject*);
extern void fn_801FE22C(void*);
extern void fn_801B05B0(s32, s32);
extern void fn_801FE934(void*, s32);
extern s32 fn_801D3A34(u32, s32);
extern s32 fn_801CEB2C(u32);
extern void fn_8014E9B0(void*, Vec3*, u8, s32, Color*, s32, s32, s32);
extern u32 fn_80201814(s32);
extern Context* fn_80201B8C(void);
extern void fn_8020123C(s32, s32, s32, s32);
extern s32 fn_80201B64(void);
extern void fn_800CDAD8(u32, s32, s32, float);
extern s32 fn_801D38E8(u32);
extern void fn_8016B400(s32, s32, s32);
extern s32 fn_801E79FC(u32, s32);
extern void fn_800CCE78(s32, s32);
extern void fn_801E7974(u32, s32);
extern u32 fn_80201AE4(void);
extern s32 fn_802066E0(u32, u32);
extern void fn_8011DD8C(s32, s32);
extern void fn_8018F76C(Effect*);
extern u32 fn_801D3944(u32);
extern void fn_8018F808(Effect*, u32*, u32*);
extern void fn_8018F864(void);
extern void* memcpy(void*, const void*, u32);
extern void fn_801E8328(s32, Effect*);

static inline s32 is_allowed(u32 object)
{
    return lbl_8023BA30[fn_801D38E8(object)].values[*lbl_8064C5A8] == 1;
}

void fn_801E2408(void* arg)
{
    GameObject* object = arg;
    Work* work = &object->work;
    u32 owner;

    if (object->type != lbl_8064D18C || (object->flags & 1) != 0) {
        fn_801FE22C(object->resource);
        if (object->handle != -1) {
            fn_801B05B0(object->handle, 10);
        }
        fn_801E237C(object);
        return;
    }

    owner = object->owner;

    switch (object->state) {
    case 0:
        fn_801FE934(object->resource, 6);
        fn_8014E9B0(work->emitter, &object->position, (u8)fn_801CEB2C(owner),
                    fn_801D3A34(owner, 0x35), &lbl_802FC5BC[3], 2, 4, 1);
        if (fn_80201814(object->id) != 0) {
            s32 current = fn_80201B8C()->current->value;
            if (current != 0) {
                fn_8020123C(0x39, current, current, 0);
            }
        }
        break;
    case 10:
        fn_8014E9B0(work->emitter, &object->position, (u8)fn_801CEB2C(owner),
                    fn_801D3A34(owner, 0x35), &lbl_802FC5BC[3], 2, 4, 1);
        break;
    case 20:
        fn_8014E9B0(work->emitter, &object->position, (u8)fn_801CEB2C(owner),
                    fn_801D3A34(owner, 0x35), &lbl_802FC5BC[3], 2, 4, 1);
        break;
    case 30:
        fn_8014E9B0(work->emitter, &object->position, (u8)fn_801CEB2C(owner),
                    fn_801D3A34(owner, 0x35), &lbl_802FC5BC[3], 2, 4, 1);
        break;
    case 40:
        fn_8014E9B0(work->emitter, &object->position, (u8)fn_801CEB2C(owner),
                    fn_801D3A34(owner, 0x35), &lbl_802FC5BC[3], 2, 4, 1);
        break;
    case 50:
        fn_8014E9B0(work->emitter, &object->position, (u8)fn_801CEB2C(owner),
                    fn_801D3A34(owner, 0x35), &lbl_802FC5BC[3], 2, 4, 1);
        break;
    case 80: {
        Effect* effect = &work->effect;
        struct {
            u32 word;
            u16 half;
        } config;
        u32 second;
        u32 first;

        config.word = lbl_80651F38;
        config.half = lbl_80651F3C;
        fn_8018F76C(effect);
        effect->value06 = 10;
        first = fn_801D3944(owner);
        second = first;
        ((Color*)&second)->a -= 50;
        ((Color*)&first)->a -= 80;
        fn_8018F808(effect, &second, &first);
        effect->callback90 = fn_8018F864;
        effect->position98.x = 320.0f;
        effect->position98.y = 240.0f;
        effect->position98.z = -1.0f;
        memcpy(effect->descriptorA4, &config, 6);
        effect->object94 = 0;
        effect->valueAA = 4;
        fn_801E8328(0x10, effect);
        break;
    }
    case 90:
        if (fn_80201814(object->id) != 0 && fn_80201B64() != 8) {
            fn_800CDAD8(object->owner, object->id, 1, 0.0f);
            switch (lbl_8064D18C) {
            case 27:
            case 345:
                if ((object->owner & 0x70000) == 0x40000 && is_allowed(object->owner))
                    fn_8016B400(1598, 0, 0);
                break;
            case 32:
                if ((object->owner & 0x70000) == 0x40000 && is_allowed(object->owner))
                    fn_8016B400(1878, 0, 0);
                break;
            case 67:
                if (is_allowed(object->owner))
                    fn_8016B400(1569, 0, 0);
                break;
            case 99:
                if (fn_801E79FC(lbl_8064C4E0, 690) == 0 && is_allowed(object->owner)) {
                    fn_800CCE78(0, 99);
                    fn_801E7974(lbl_8064C4E0, 690);
                }
                break;
            case 196:
                if (fn_802066E0(fn_80201AE4(), 0xE98A39BB) != 0) {
                    if (is_allowed(object->owner))
                        fn_8016B400(2783, 0, 0);
                    else
                        fn_8011DD8C(4, 0);
                }
                break;
            case 255:
                if (is_allowed(object->owner))
                    fn_8016B400(1861, 0, 0);
                break;
            }
        }
        break;
    case 128: {
        void (*callback)(GameObject*, u32) = object->callback;
        if (callback != 0)
            callback(object, object->callback_arg);
        fn_801E237C(object);
        break;
    }
    }
}
