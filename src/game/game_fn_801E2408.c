typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;

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
extern float lbl_80651220;
extern float lbl_80651224;
extern float lbl_80651228;
extern float lbl_8065122C;
extern u8 lbl_802FC5BC[];
extern LookupRow lbl_8023BA30[];

extern void fn_801E237C(void*);
extern void fn_801FE22C(void*);
extern void fn_801B05B0(s32, s32);
extern void fn_801FE934(void*, s32);
extern s32 fn_801D3A34(u32, s32);
extern s32 fn_801CEB2C(u32);
extern void fn_8014E9B0(void*, void*, u8, s32, void*, s32, s32, s32);
extern s32 fn_80201814(s32);
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
extern void fn_8018F76C(void*);
extern u32 fn_801D3944(u32);
extern void fn_8018F808(void*, u32*, u32*);
extern void fn_8018F864(void);
extern void* memcpy(void*, const void*, u32);
extern void fn_801E8328(s32, void*);

static s32 is_allowed(u32 object)
{
    return lbl_8023BA30[fn_801D38E8(object)].values[*lbl_8064C5A8] == 1;
}

void fn_801E2408(u8* object)
{
    u8* work = object + 0xBC;
    u32 subject = *(u32*)(object + 4);
    s32 id;
    u8 kind;

    if (*(s32*)(object + 8) != lbl_8064D18C || (object[0xFF0] & 1) != 0) {
        fn_801FE22C(*(void**)(object + 0x44));
        if (*(s32*)(object + 0x10) != -1) {
            fn_801B05B0(*(s32*)(object + 0x10), 10);
        }
        fn_801E237C(object);
        return;
    }

    switch (*(u16*)(object + 0xFF4)) {
    case 0:
        fn_801FE934(object + 0x44, 6);
        id = fn_801D3A34(subject, 0x35);
        kind = (u8)fn_801CEB2C(subject);
        fn_8014E9B0(work, object + 0x38, kind, id, lbl_802FC5BC + 0xC, 2, 4, 1);
        if (fn_80201814(*(s32*)(object + 0xC)) != 0) {
            s32 current = fn_80201B8C()->current->value;
            if (current != 0) {
                fn_8020123C(0x39, current, current, 0);
            }
        }
        break;
    case 10:
        id = fn_801D3A34(subject, 0x35);
        kind = (u8)fn_801CEB2C(subject);
        fn_8014E9B0(work, object + 0x38, kind, id, lbl_802FC5BC + 0xC, 2, 4, 1);
        break;
    case 20:
        id = fn_801D3A34(subject, 0x35);
        kind = (u8)fn_801CEB2C(subject);
        fn_8014E9B0(work, object + 0x38, kind, id, lbl_802FC5BC + 0xC, 2, 4, 1);
        break;
    case 30:
        id = fn_801D3A34(subject, 0x35);
        kind = (u8)fn_801CEB2C(subject);
        fn_8014E9B0(work, object + 0x38, kind, id, lbl_802FC5BC + 0xC, 2, 4, 1);
        break;
    case 40:
        id = fn_801D3A34(subject, 0x35);
        kind = (u8)fn_801CEB2C(subject);
        fn_8014E9B0(work, object + 0x38, kind, id, lbl_802FC5BC + 0xC, 2, 4, 1);
        break;
    case 50:
        id = fn_801D3A34(subject, 0x35);
        kind = (u8)fn_801CEB2C(subject);
        fn_8014E9B0(work, object + 0x38, kind, id, lbl_802FC5BC + 0xC, 2, 4, 1);
        break;
    case 80: {
        u8* effect = work + 0xB0;
        struct {
            u32 word;
            u16 half;
        } config;
        u32 first;
        u32 second;

        config.word = lbl_80651F38;
        config.half = lbl_80651F3C;
        fn_8018F76C(effect);
        *(u16*)(effect + 6) = 10;
        first = fn_801D3944(subject);
        second = first;
        ((u8*)&first)[3] -= 80;
        ((u8*)&second)[3] -= 50;
        fn_8018F808(effect, &second, &first);
        *(void (**)(void))(effect + 0x90) = fn_8018F864;
        *(float*)(effect + 0x98) = lbl_80651220;
        *(float*)(effect + 0x9C) = lbl_80651224;
        *(float*)(effect + 0xA0) = lbl_80651228;
        memcpy(effect + 0xA4, &config, 6);
        *(u32*)(effect + 0x94) = 0;
        effect[0xAA] = 4;
        fn_801E8328(0x10, effect);
        break;
    }
    case 90:
        if (fn_80201814(*(s32*)(object + 0xC)) != 0 && fn_80201B64() != 8) {
            fn_800CDAD8(subject, *(s32*)(object + 0xC), 1, lbl_8065122C);
            switch (lbl_8064D18C) {
            case 27:
            case 345:
                if ((subject & 0x70000) == 0x40000 && is_allowed(subject))
                    fn_8016B400(1598, 0, 0);
                break;
            case 32:
                if ((subject & 0x70000) == 0x40000 && is_allowed(subject))
                    fn_8016B400(1878, 0, 0);
                break;
            case 67:
                if (is_allowed(subject))
                    fn_8016B400(1569, 0, 0);
                break;
            case 99:
                if (fn_801E79FC(lbl_8064C4E0, 690) == 0 && is_allowed(subject)) {
                    fn_800CCE78(0, 99);
                    fn_801E7974(lbl_8064C4E0, 690);
                }
                break;
            case 196:
                if (fn_802066E0(fn_80201AE4(), 0xE98A39BB) != 0) {
                    if (is_allowed(subject))
                        fn_8016B400(2783, 0, 0);
                    else
                        fn_8011DD8C(4, 0);
                }
                break;
            case 255:
                if (is_allowed(subject))
                    fn_8016B400(1861, 0, 0);
                break;
            }
        }
        break;
    case 128: {
        void (*callback)(u8*, u32) = *(void (**)(u8*, u32))(object + 0x28);
        if (callback != 0)
            callback(object, *(u32*)(object + 0x2C));
        fn_801E237C(object);
        break;
    }
    }
}
