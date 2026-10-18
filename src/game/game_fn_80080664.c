typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct ResourceKey {
    u32 word;
    u16 half;
} ResourceKey;

typedef struct EffectDesc {
    u8 kind;
    u8 width;
    u8 alpha;
    signed char mode;
    u8 pad04[2];
    u16 count;
    u16 height;
    u8 pad0A[0x0A];
    u16 lifetime;
    u16 fade;
    u8 color[4];
    u8 pad1C;
    u8 flags;
    u8 pad1E[2];
    u8 variant;
    u8 pad21;
    u8 enabled;
    u8 pad23[0x6D];
} EffectDesc;

typedef struct ModeState {
    u8 pad00[8];
    int mode;
} ModeState;

typedef struct QuakeState {
    u8 pad000[0x1C4];
    u32 timer;
    u16 fadeTimer;
    u8 volume;
} QuakeState;

typedef struct SoundState {
    u8 pad000[0x60C];
    int quakeSound;
} SoundState;

extern ModeState lbl_803003C8;
extern int lbl_8064D18C;
extern QuakeState lbl_8031CBA0;
extern SoundState lbl_8031CD84;
extern Vec3 lbl_802393C0;
extern Vec3 lbl_802393CC;
extern u32 lbl_8064EA6C;
extern u16 lbl_8064EA70;
extern u32 lbl_8064EA74;
extern int lbl_8064D5A8;

extern void *fn_80201B3C();
extern void fn_80201E78(Vec3 *, void *);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern void fn_801F74C8(int, int, int);
extern void fn_801441C0(int, int, int);
extern int fn_801B05E8(int, u8, int, int, int, int, int, int);
extern int rand(void);
extern void fn_8019D560(EffectDesc *);
extern void *fn_80152F90(Vec3 *, void *, u8 *, u8);
extern int fn_801B0A28(int);
extern int fn_801AF85C(int);
extern void fn_801B09F0(int, int);
extern void fn_801B05B0(int, int);

void fn_80080664(void)
{
    u32 color;
    ResourceKey key;
    Vec3 origin;
    Vec3 position;
    EffectDesc effect;
    void *object;
    u32 distance;
    u8 alpha;
    int shakeKind;
    int shakeLevel;
    int rumble;
    u8 volume;
    int level;
    int sample;

    if ((lbl_803003C8.mode == 6 && lbl_8064D18C == 0x137) ||
        (lbl_803003C8.mode == 2 && lbl_8064D18C == 0x91)) {
        if (lbl_8031CBA0.timer == 0) {
            shakeLevel = 1;
            volume = 100;
            key.word = lbl_8064EA6C;
            key.half = lbl_8064EA70;
            color = lbl_8064EA74;
            origin = lbl_802393C0;
            position = lbl_802393CC;
            object = fn_80201B3C();
            if (object != 0) {
                fn_80201E78(&origin, object);
            }
            distance = fn_80178E94(&position, &origin);
            if (distance < 1500) {
                rumble = 5;
                shakeKind = 3;
                volume = 127;
            } else if (distance < 3000) {
                shakeKind = 2;
                shakeLevel = 2;
                rumble = 3;
            } else if (distance < 5000) {
                shakeKind = 2;
                shakeLevel = 3;
                rumble = 2;
            } else if (distance < 7500) {
                shakeKind = 2;
                shakeLevel = 3;
                rumble = 1;
                volume = 50;
            } else {
                shakeKind = 1;
                shakeLevel = 3;
                rumble = 1;
                volume = 50;
            }
            lbl_8031CBA0.volume = volume;
            fn_801F74C8(350, 1, rumble);
            fn_801441C0(shakeKind, shakeLevel, 90);
            lbl_8031CBA0.fadeTimer = 350;
            lbl_8031CD84.quakeSound = fn_801B05E8(0x248, volume, 4, 1, 0, 5, 0, 0);
            lbl_8031CBA0.timer = rand() % 1000 + 700;
            fn_8019D560(&effect);

            alpha = ((u8 *)&color)[3];
            effect.kind = 32;
            effect.width = 32;
            effect.count = 120;
            effect.height = 48;
            effect.mode = -1;
            effect.alpha = alpha;
            effect.lifetime = 100;
            effect.fade = 2;
            effect.color[0] = ((u8 *)&color)[0];
            effect.color[1] = ((u8 *)&color)[1];
            effect.color[2] = ((u8 *)&color)[2];
            effect.color[3] = alpha;
            effect.variant = 5;
            effect.enabled = 0;
            effect.flags = 32;
            fn_80152F90(&position, &key, (u8 *)&effect, 200);
        }
        if (lbl_8031CBA0.fadeTimer != 0) {
            if (--lbl_8031CBA0.fadeTimer < 200) {
                sample = fn_801B0A28(lbl_8031CD84.quakeSound);
                if (lbl_8064D5A8 % (260 / lbl_8031CBA0.volume) == 0) {
                    level = sample - 1;
                    if ((u8)level > 127) {
                        level = 0;
                        lbl_8031CBA0.fadeTimer = 0;
                    }
                    if (fn_801AF85C(lbl_8031CD84.quakeSound) != 0) {
                        fn_801B09F0(lbl_8031CD84.quakeSound, level);
                    }
                }
            }
            if (lbl_8031CBA0.fadeTimer == 0 && fn_801AF85C(lbl_8031CD84.quakeSound) != 0) {
                fn_801B05B0(lbl_8031CD84.quakeSound, 0);
            }
        }
        lbl_8031CBA0.timer--;
    }
}
