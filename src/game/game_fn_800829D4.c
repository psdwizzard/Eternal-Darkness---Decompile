typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Color {
    u8 channel[4];
} Color;

typedef struct Effect {
    u32 id;
    u32 owner;
    u32 unknown08;
    u32 velocity;
    u32 acceleration;
    u8 pad14[8];
    Vec3 position;
    Color color;
    u16 field2C;
    u16 field2E;
    u16 field30;
    u16 field32;
    u16 field34;
    u8 field36;
    u8 field37;
    u8 field38;
    u8 pad39[0xF];
    int (*callback)(u32);
    u8 pad4C[0x2C];
} Effect;
typedef struct RuntimeState {
    u8 pad[0x498];
    u32 sounds[3];
    Effect effects[3];
} RuntimeState;
typedef struct GameState {
    u8 pad0[0x1CB];
    s8 screen;
    u8 pad1[0x1E0 - 0x1CC];
    u8 effectMask[3];
} GameState;

extern GameState lbl_8031CBA0;
extern RuntimeState lbl_8031CD84;
extern int lbl_8064D18C;
extern u32 lbl_8064C508;
extern void *lbl_8064C8E8;
extern u32 lbl_8064C8EC;
extern Color lbl_8064B58C;
extern const Color lbl_8064EAB4;
extern const Color lbl_8064EAB8;
extern const Color lbl_806519A4;
extern int fn_8008250C(u32);
extern void fn_8007D744(int);
extern int fn_802019EC(int, int);
extern void *fn_80201814(int);
extern void *fn_80201BC8(void *);
extern void fn_801FD534(u32);
extern int fn_801FE25C(u32);
extern void fn_801FE96C(u32, int);
extern void fn_801FE9A4(u32, int);
extern void fn_8014CBC0(void *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern int fn_801E8328(u32, u32);
extern void fn_801E5FB0(u32);
extern int fn_801E6CA0(u32, int, int, int, int);
extern void fn_801A98F4(int, int);
extern void fn_8012DBE8(void *, int, Color *);
extern void *fn_8012C62C(void *, int, Color *, Color *, Color *, int);
extern void fn_80144680(void *);
extern void fn_80144C40(void);
extern void fn_8016B400(int, int, int);

void fn_800829D4(short index)
{
    u8 bit = 1 << index;
    int variant = 0;
    s8 alpha;
    int sound;
    u8 *object;
    Vec3 position;
    Color base, start, mid, rate, end, target;
    u8 finalMask;

    switch (lbl_8064D18C) {
    case 0xDA: variant = 1; break;
    case 0x47: variant = 2; break;
    }
    fn_801E5FB0(lbl_8031CD84.sounds[index]);
    if (lbl_8031CBA0.effectMask[variant] & bit) {
        sound = 0;
        switch (index) {
        case 1: sound = 2; break;
        case 2: sound = 4; break;
        }
        lbl_8031CBA0.effectMask[variant] &= ~bit;
        lbl_8031CD84.sounds[index] = fn_801E6CA0(lbl_8064C508, 2, sound, 0, 1);
        alpha = -5;
        fn_801A98F4(0x201, 100);
    } else {
        sound = 1;
        switch (index) {
        case 1: sound = 3; break;
        case 2: sound = 5; break;
        }
        lbl_8031CBA0.effectMask[variant] |= bit;
        lbl_8031CD84.sounds[index] = fn_801E6CA0(lbl_8064C508, 2, sound, 0, 1);
        alpha = 5;
    }
    object = fn_80201BC8(fn_80201814(fn_802019EC(index + 0x822, lbl_8064D18C)));
    if (object != 0) {
        base = lbl_8064EAB4;
        fn_8012DBE8(object, 15, &base);
        target = lbl_8064EAB8;
        target.channel[3] = alpha > 0 ? 0xFF : 0;
        rate = lbl_806519A4;
        rate.channel[3] = alpha;
        mid = rate;
        end = target;
        start = base;
        fn_8012C62C(object, 15, &start, &mid, &end, 4);
        if (alpha > 0) {
            if (fn_801FE25C(lbl_8031CD84.effects[index].id) != 0) {
                fn_801FE9A4(lbl_8031CD84.effects[index].id, 1);
                fn_801FE96C(lbl_8031CD84.effects[index].id, 0);
            } else {
                fn_801FD534(lbl_8031CD84.effects[index].id);
                fn_8014CBC0(&lbl_8031CD84.effects[index]);
                lbl_8031CD84.effects[index].id = 0;
                lbl_8031CD84.effects[index].owner = 0;
                fn_8011F114(&position, (Vec3 *)object);
                lbl_8031CD84.effects[index].position = position;
                lbl_8031CD84.effects[index].color = lbl_8064B58C;
                lbl_8031CD84.effects[index].callback = fn_8008250C;
                lbl_8031CD84.effects[index].field2C = 0;
                lbl_8031CD84.effects[index].field30 = 0;
                lbl_8031CD84.effects[index].field32 = 1;
                lbl_8031CD84.effects[index].velocity = 0;
                lbl_8031CD84.effects[index].acceleration = 0;
                lbl_8031CD84.effects[index].field36 = 25;
                lbl_8031CD84.effects[index].field37 = 0;
                lbl_8031CD84.effects[index].field38 = 5;
                fn_801E8328(0x13, (u32)&lbl_8031CD84.effects[index]);
            }
        } else {
            fn_801FE9A4(lbl_8031CD84.effects[index].id, 0);
            lbl_8031CD84.effects[index].id = 0;
        }
    }
    finalMask = 2;
    switch (lbl_8064D18C) {
    case 0xDA: finalMask = 0; break;
    case 0x47: finalMask = 1; break;
    }
    if (lbl_8031CBA0.effectMask[variant] == finalMask) {
        fn_801E5FB0(lbl_8031CD84.sounds[0]);
        fn_801E5FB0(lbl_8031CD84.sounds[1]);
        fn_801E5FB0(lbl_8031CD84.sounds[2]);
        lbl_8031CD84.sounds[0] = 0;
        lbl_8031CD84.sounds[1] = 0;
        lbl_8031CD84.sounds[2] = 0;
        fn_80144680(lbl_8064C8E8);
        lbl_8031CBA0.screen = -1;
        fn_801E5FB0(lbl_8064C8EC);
        lbl_8064C8E8 = 0;
        lbl_8064C8EC = 0;
        fn_80144C40();
        switch (lbl_8064D18C) {
        case 0xD9: fn_8016B400(0x5FE, 0, 0); break;
        case 0xDA: fn_8016B400(0x5FF, 0, 0); break;
        case 0x47: fn_8016B400(0x420, 0, 0); break;
        }
    }
    fn_8007D744(11);
}
