typedef signed int s32;
typedef unsigned short u16;
typedef float f32;

typedef struct Vec3 {
    f32 x, y, z;
} Vec3;

extern int fn_80201B54(void *);
extern void *fn_800A1D28(void *);
extern void *fn_801294DC(void *, int, int, int);
extern void fn_802045AC(void *, Vec3 *);
extern f32 fn_8012B7D0(void *, Vec3);
extern void fn_80129BA4(void *, f32, f32);
extern void fn_80128C28(void *, void (*)(void), int);
extern void fn_80128C44(void *, void (*)(void), int);
extern void fn_801287C4(void *, void *, void *, s32);
extern void fn_80201D2C(void *, int);
extern void fn_80201D14(void *, int);
extern void fn_80204810(void);
extern void fn_800A1A04(void);
extern void fn_800D36F4(void);
extern void fn_800D3718(void);
extern void fn_800D386C(void);

extern f32 lbl_8064F348;

int fn_800D00EC(void *actor, void *target, int type) {
    int result;
    int anim;
    void *effect;
    int id;
    int flags;
    int sound;
    Vec3 pos;

    result = 1;
    flags = 0x104;
    sound = 0;
    id = fn_80201B54(actor);
    fn_800A1D28(actor);
    switch (type) {
    case 0:
        anim = 0x6C;
        sound = 0x4C;
        break;
    case 1:
        flags |= 1;
        anim = 0x6D;
        sound = 0x4D;
        break;
    case 2:
        anim = 0x6E;
        sound = 0xC;
        break;
    case 3:
        anim = 0xF;
        flags |= 1;
        break;
    }
    effect = fn_801294DC(target, anim, flags, 6);
    if (effect != 0) {
        fn_802045AC(actor, &pos);
        fn_80129BA4(effect, fn_8012B7D0(target, pos), lbl_8064F348);
        if (sound != 0) {
            fn_80128C28(effect, fn_80204810, (id << 8) | (u16)sound);
        }
        fn_80128C44(effect, fn_80204810, (id << 8) | 7);
        if (type == 0) {
            fn_80201D2C(actor, 0x77);
            fn_80201D14(actor, 1);
        } else if (type == 1) {
            fn_801287C4(effect, fn_800D36F4, actor, 0x2D);
            fn_801287C4(effect, fn_800D3718, actor, 0x3C);
            fn_801287C4(effect, fn_800A1A04, (void *)0x10000, 0x2A);
            fn_801287C4(effect, fn_800A1A04, (void *)0x1C28, 0x32);
            fn_801287C4(effect, fn_800A1A04, (void *)0x10000, 0x39);
            fn_801287C4(effect, fn_800D386C, (void *)0x1C28, 0x41);
        } else if (type == 2) {
            fn_801287C4(effect, fn_800A1A04, (void *)0x6666, 0x48);
            fn_801287C4(effect, fn_800A1A04, (void *)0x10000, 0x58);
        }
    } else {
        result = 0;
    }
    return result;
}
