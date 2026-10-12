typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

enum SoundCode { SOUND_MODE_ONE = 0x11, SOUND_OTHER_MODES = 0x12 };

typedef struct ActionState {
    void *event;
    u8 reserved04[0x84];
    u16 selection[4];
    u8 flags;
    u8 mode;
    u8 reserved92[2];
    u8 cooldown;
} ActionState;

typedef struct ActionContext {
    ActionState *state;
} ActionContext;

typedef union Conversion {
    double value;
    struct { u32 high, low; } words;
} Conversion;

typedef struct Item {
    u8 reserved00[0xC];
    int kind;
} Item;

extern u32 lbl_8064CA8C;
extern int lbl_8064D18C;
extern float lbl_8064F110;
extern float lbl_8064F194;
extern double lbl_8064F1A0;
extern double lbl_8064F158;
extern float lbl_8064F1A8;
extern float lbl_8064F1AC;

extern void *fn_8004914C();
extern void *fn_800C1D54(void);
extern int fn_800C34A8(void *, void *, void *);
extern u32 fn_800C3958(void *, u32);
extern double fn_8010181C(double);
extern int fn_8011EB04(void *);
extern void *fn_8011F130(void *);
extern int fn_8011FCE4(void *);
extern void fn_801287C4(void *, void *, u32, u32);
extern void fn_80128C28(void *, u32, u32);
extern void fn_80128C44(void *, u32, u32);
extern u16 fn_801291CC(void *);
extern int fn_80129334(void *, int, int *, int);
extern void *fn_801294DC(void *, int, int, int);
extern int fn_801296F8(void *, int);
extern int fn_8012A1BC(void *, int);
extern int fn_8012A1FC(void *, int);
extern u8 fn_8015793C(void *);
extern void fn_80157B80(void *, u32);
extern void *fn_801A717C(void);
extern void fn_801A7324(const void *, void *);
extern void fn_801A742C(void *, u16);
extern u16 fn_801A7434(void *);
extern void fn_801A7460(void *, u32);
extern u32 fn_801A7468(void *);
extern void fn_801A7478(void *, u32);
extern void fn_801A74A0(void *, u32);
extern u32 fn_801A74C0(void *);
extern u32 fn_801A74C8(void *, u32);
extern void fn_801A7518(void *, s16);
extern void fn_801A7538(void *, u16);
extern void fn_801A7550(void *, u32);
extern void fn_801A7558(void *, u32);
extern u32 fn_801A7560(void *, u32);
extern u32 fn_801A7570(void *);
extern void fn_801A7598(void *, u16);
extern void fn_801A75A8(void *, u8);
extern void fn_801A75B8(void *, float);
extern void fn_801A7644(void *, u8);
extern void fn_801A764C(void *, const void *);
extern u32 fn_801A76B0(void *);
extern void *fn_801A7778(void *);
extern u32 fn_801A77D4(void *);
extern u16 fn_801A77F8(void *);
extern void *fn_80200C38(void **);
extern u64 fn_8020123C(int, int, int, int);
extern int fn_80201B54(void *);
extern void *fn_80201B8C(void *);
extern void *fn_80201B94(void *);
extern void *fn_80201BC8(void *);
extern void *fn_80201C48(void *);

extern int fn_8003BAD8(void *, void *);
extern int fn_800C1D60(void *, void *);
extern int fn_800C36F0(void *, void *);
extern int fn_800C3A74(void *, void *);
extern int fn_800C3ADC(void *, void *);
extern int fn_801A9FA4(void *, u32);
extern int fn_80204230(int, int);
extern int fn_802042A4(int, int);

int fn_800C28D8(void *object, void **node)
{
    int frame;
    Conversion second;
    Conversion first;
    ActionContext *context;
    void *source;
    void *parent;
    void *owner;
    void *linked;
    int needsSound;
    ActionState *state;
    int result;
    int objectId;
    int animation;
    int ownerKind;
    int blocked;
    void *queue;
    Item *item;
    s16 strength;
    u32 flags;
    void *event;
    void *model;
    int kind;

    context = fn_80201B8C(object);
    source = fn_80200C38(node);
    parent = fn_80201B94(object);
    owner = fn_80201BC8(object);
    linked = fn_80201C48(parent);
    objectId = fn_80201B54(object);
    state = context->state;
    result = 0;
    needsSound = 0;
    blocked = 0;
    ownerKind = fn_8011EB04(owner);

    if (fn_801A7434(source) == 0x100 &&
        (!(lbl_8064CA8C & 3) || (lbl_8064CA8C & 4))) {
        u32 value;
        fn_801A742C(source, 1);
        value = fn_801A77D4(source);
        fn_801A7460(source, value);
        state->flags &= ~4;
        state->flags |= 8;
        state->cooldown = 10;
    }
    animation = fn_801A7468(source);
    if ((fn_801291CC(owner) <= 5 && (state->flags & 8)) ||
        context->state->cooldown != 0) {
        blocked = 1;
    }
    if (!blocked) {
        queue = fn_801294DC(owner, animation, 0, 6);
        if (queue != 0) {
            fn_801A74C0(source);
            flags = fn_801A7570(source);
            item = fn_801A7778(source);
            strength = item != 0 ? (u8)fn_8015793C(item) : 0;
            if (strength <= 0) {
                strength = 3;
            }
            if (fn_8011FCE4(owner) == 0x13) {
                fn_801296F8(owner, 0xB333);
            } else {
                fn_801296F8(owner, 0x10000);
            }
            event = fn_801A717C();
            fn_801A7324(source, event);
            fn_801A74A0(event, objectId);
            fn_801A7560(event, flags | 0x100600);
            fn_801A7538(event, 1);
            fn_801A7550(event, 12);
            fn_801A7558(event, 12);
            fn_801A764C(event, fn_8011F130(owner));
            if (lbl_8064D18C == 0xEF) {
                fn_801A7598(source, 400);
            }
            {
                u8 mask = (u8)fn_801A77F8(source);
                fn_801A75A8(event, (u8)(mask | fn_801A76B0(source)));
            }
            if (fn_801A74C0(source) & 4) {
                register s16 amount;
                flags = fn_801A74C0(source);
                if (state->flags & 2) {
                    register float factor;
                    register double biased;
                    register double bias;
                    register float converted;
                    register float scaled;
                    register double integral;
                    first.words.low = (u32)(int)strength ^ 0x80000000;
                    first.words.high = 0x43300000;
                    biased = first.value;
                    bias = lbl_8064F158;
                    factor = lbl_8064F1A8;
                    /* ASM: fsubs, fmuls perform the shared-bias conversion
                     * at single precision; C emits fsub followed by frsp. */
                    asm {
                        fsubs converted, biased, bias
                        fmuls scaled, converted, factor
                    }
                    integral = lbl_8064F1A0 > fn_8010181C(scaled) ?
                        lbl_8064F1A0 : fn_8010181C(scaled);
                    /* ASM: fctiwz, stfd, lwz use the opposite conversion
                     * slot and preserve MWCC's float-to-short calling form.
                     * C allocates another slot or adds sign extension. */
                    asm {
                        fctiwz integral, integral
                        stfd integral, second.value
                        lwz amount, second.words.low
                    }
                } else if (state->flags & 4) {
                    amount = 0;
                } else {
                    register float factor;
                    register double biased;
                    register double bias;
                    register float converted;
                    register float scaled;
                    register double integral;
                    second.words.low = (u32)(int)strength ^ 0x80000000;
                    second.words.high = 0x43300000;
                    biased = second.value;
                    bias = lbl_8064F158;
                    factor = lbl_8064F194;
                    /* ASM: fsubs, fmuls perform the shared-bias conversion
                     * at single precision; C emits fsub followed by frsp. */
                    asm {
                        fsubs converted, biased, bias
                        fmuls scaled, converted, factor
                    }
                    integral = lbl_8064F1A0 > fn_8010181C(scaled) ?
                        lbl_8064F1A0 : fn_8010181C(scaled);
                    /* ASM: fctiwz, stfd, lwz use the opposite conversion
                     * slot and preserve MWCC's float-to-short calling form.
                     * C allocates another slot or adds sign extension. */
                    asm {
                        fctiwz integral, integral
                        stfd integral, first.value
                        lwz amount, first.words.low
                    }
                }
                fn_801A7518(event, amount);
                fn_801A74C8(event, flags | 0x1001);
            } else {
                fn_801A7518(event, strength);
            }
            model = fn_8004914C(source);
            if (model != 0) {
                switch (fn_8011EB04(model)) {
                case 0x3D:
                case 0x3E:
                case 0x62:
                case 0x6E:
                case 0x7A:
                    fn_801A74C8(event, fn_801A74C0(event) | 0x1000);
                    break;
                }
            }
            if (state->flags & 4) {
                register int mask = fn_800C34A8(state->selection, (void *)state->mode, source);
                register u8 soundMask;
                register u32 maskByte;
                float scale;
                /* ASM: clrlwi, mr retain both the masked comparison value and
                 * the original return register for the byte-valued setter.
                 * C merges these values or inserts an extra byte mask. */
                asm {
                    clrlwi maskByte, mask, 24
                    mr soundMask, mask
                }
                scale = maskByte == 0x10 ? lbl_8064F1AC : lbl_8064F110;
                fn_801A75A8(event, soundMask);
                fn_801A75B8(event, scale);
                needsSound = 1;
            } else if ((state->flags & 2) && !(state->flags & 8)) {
                needsSound = 1;
            }
            fn_801A7644(event, state->flags);
            if (needsSound) {
                int soundFrame = fn_8012A1FC(owner, animation) + 1;
                fn_801287C4(queue, fn_801A9FA4,
                    (u16)(state->mode == 1 ? SOUND_MODE_ONE : SOUND_OTHER_MODES), soundFrame);
                if (state->mode != 0) {
                    fn_800C3958((void *)state->mode,
                        fn_800C34A8(state->selection, (void *)state->mode, source));
                }
            }
            if (fn_80129334(owner, 1, &frame, -1) != -1) {
                if (item != 0 && item->kind != 0x62) {
                    fn_80157B80(item, 4);
                    fn_801A7478(event, (u32)fn_800C1D54());
                    fn_801287C4(queue, fn_800C3ADC, (u32)event, frame - 2);
                }
                fn_801287C4(queue, fn_8003BAD8, (u32)event, frame - 2);
                fn_801287C4(queue, fn_800C1D60, (u32)event, frame - 1);
                fn_801287C4(queue, fn_800C1D60, (u32)event, frame);
                fn_801287C4(queue, fn_800C1D60, (u32)event, frame + 1);
                fn_801287C4(queue, fn_800C1D60, (u32)event, frame + 2);
                fn_80128C28(queue, (u32)fn_80204230, (u32)event);
                fn_80128C44(queue, (u32)fn_802042A4, (u32)event);
                if (!(state->flags & 0xC)) {
                    fn_801287C4(queue, fn_800C3A74, 1, frame + 2);
                    fn_801287C4(queue, fn_800C3A74, 0,
                        fn_8012A1BC(owner, animation) - 1);
                }
            }
            model = fn_8004914C(event);
            kind = model != 0 ? fn_8011EB04(model) : -1;
            if (kind == 0xD2 && ownerKind == 0x51 && fn_801A7434(source) == 2) {
                fn_801287C4(queue, fn_800C36F0, (u32)event, 16);
                fn_801287C4(queue, fn_800C36F0, (u32)event, 22);
            }
            if ((int)linked != 0) {
                fn_8020123C(10, objectId, (int)linked, (int)event);
            }
            context->state->event = event;
            lbl_8064CA8C = 0;
            result = 1;
        }
    }
    return result;
}
