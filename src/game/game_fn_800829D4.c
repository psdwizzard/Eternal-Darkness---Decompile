typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct TextDescriptor TextDescriptor;
typedef struct Entry Entry;
typedef struct Entry80201814 Entry80201814;

typedef struct Vec3 { float x, y, z; } Vec3;
typedef union Color {
    u32 word;
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
    TextDescriptor *labels[3];
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
extern void *lbl_8064C508;
extern Entry *lbl_8064C8E8;
extern void *lbl_8064C8EC;
extern Color lbl_8064B58C;
extern const Color lbl_8064EAB4;
extern const Color lbl_8064EAB8;
extern const Color lbl_806519A4;
extern int fn_8008250C(u32);
extern void fn_8007D744(int);
extern int fn_802019EC(int, int);
extern Entry80201814 *fn_80201814(int);
extern void *fn_80201BC8(void *);
extern void fn_801FD534(u32);
extern int fn_801FE25C(u32);
extern void fn_801FE96C(u32, u16);
extern void fn_801FE9A4(u32, u16);
extern void fn_8014CBC0(void *);
extern void fn_8011F114(Vec3 *, Vec3 *);
extern int fn_801E8328(u32, u32);
extern void fn_801E5FB0(void *);
extern TextDescriptor *fn_801E6CA0(void *, u32, u32, u32, int);
extern int fn_801A98F4(int, void *);
extern u16 fn_8012DBE8(u8 *, u32, u8 *);
extern void *fn_8012C62C(u8 *, int, void *, s8 *, void *, int);
extern void fn_80144680(Entry *);
extern void fn_80144C40(void);
extern void fn_8016B400(int, void *, void *);

static inline void applyFade(u8 *object, register s8 alpha, Color *base)
{
    volatile Color target;
    Color end;
    volatile Color rate;
    Color mid, start;
    register int direction, negative;
    u32 templateWord;
    u8 opacity;

    /* ASM: extsb keeps sign extension before the template read;
     * C hoists the template loads before this conversion. */
    asm { extsb direction, alpha }
    templateWord = lbl_8064EAB8.word;
    /* ASM: neg preserves the dependency between template reads;
     * C schedules the reads together. */
    asm { neg negative, direction }
    rate = lbl_806519A4;
    opacity = (negative & ~direction) < 0 ? 255 : 0;
    rate.channel[3] = alpha;
    target.word = templateWord;
    mid = rate;
    target.channel[3] = opacity;
    end = target;
    start = *base;
    fn_8012C62C(object, 15, &start, (s8 *)&mid, &end, 4);
}

void fn_800829D4(short index)
{
    u8 bit = 1 << index;
    int variant = 0;
    s8 alpha;
    int labelIndex;
    u8 *object;
    Vec3 position;
    Color base;
    u8 finalMask;

    switch (lbl_8064D18C) {
    case 0xDA: variant = 1; break;
    case 0x47: variant = 2; break;
    }
    fn_801E5FB0(lbl_8031CD84.labels[index]);
    if (lbl_8031CBA0.effectMask[variant] & bit) {
        labelIndex = 0;
        switch (index) {
        case 1: labelIndex = 2; break;
        case 2: labelIndex = 4; break;
        }
        lbl_8031CBA0.effectMask[variant] &= ~bit;
        lbl_8031CD84.labels[index] = fn_801E6CA0(lbl_8064C508, 2, labelIndex, 0, 1);
        alpha = -5;
        fn_801A98F4(0x201, (void *)100);
    } else {
        labelIndex = 1;
        switch (index) {
        case 1: labelIndex = 3; break;
        case 2: labelIndex = 5; break;
        }
        lbl_8031CBA0.effectMask[variant] |= bit;
        lbl_8031CD84.labels[index] = fn_801E6CA0(lbl_8064C508, 2, labelIndex, 0, 1);
        alpha = 5;
    }
    object = fn_80201BC8(fn_80201814(fn_802019EC(index + 0x822, lbl_8064D18C)));
    if (object != 0) {
        base = lbl_8064EAB4;
        fn_8012DBE8(object, 15, base.channel);
        applyFade(object, alpha, &base);
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
        fn_801E5FB0(lbl_8031CD84.labels[0]);
        fn_801E5FB0(lbl_8031CD84.labels[1]);
        fn_801E5FB0(lbl_8031CD84.labels[2]);
        lbl_8031CD84.labels[0] = 0;
        lbl_8031CD84.labels[1] = 0;
        lbl_8031CD84.labels[2] = 0;
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
