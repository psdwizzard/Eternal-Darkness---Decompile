typedef signed char s8;
typedef unsigned char u8;
typedef unsigned long long u64;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef float f32;

typedef struct GlyphTable {
    u16 ids[11];
} GlyphTable;

extern const u16 lbl_802391D0[12];
extern f32 lbl_8064E910;
extern f32 lbl_8064E914;
extern f32 lbl_8064E918;

extern s32 fn_8003BD48(void *, void *);
extern s32 fn_80078608(void *, s32 *, void **, void **, void **, s32 *, s32 *, s32 *);
extern void *fn_800CA3A0(void *, s32, void *, s32);
extern int fn_800FBFB0(void);
extern void *fn_8011F130(void *);
extern void fn_80120AD0(void *, int, int, int, float, float);
extern int fn_80128B10(void *, u32);
extern int fn_80128EAC(void *);
extern u8 fn_80128EE4(void *);
extern s32 fn_80128F74(void *, u32);
extern int fn_801290D0(void *);
extern void *fn_801A7498(void *);
extern void *fn_801A74B8(void *);
extern void fn_801A74D8(void *, u32);
extern void fn_801A74E8(void *, u32);
extern int fn_801AC9F4(int, int, void *, int);
extern void fn_8020104C(int, void *, void *, int, float);
extern u64 fn_8020123C(int, void *, void *, void *);
extern void *fn_80201814(void *);
extern void *fn_80201B8C(void *);
extern void *fn_80201BC8(void *);

typedef struct Slot {
    s32 pad;
    s32 type;
} Slot;

typedef struct Ring {
    Slot slots[6];
    s32 index;
    char pad34[0x3E - 0x34];
    u16 timer;
    char pad40[0x42 - 0x40];
    s8 need3;
    s8 need4;
    s8 need6;
} Ring;

typedef struct Owner {
    char pad0[0xC];
    Ring *ring;
    char pad10[0x94 - 0x10];
    s32 mode;
} Owner;

int fn_80078794(void *obj, void *arg) {
    void *a;
    void *b;
    s32 type;
    s32 first;
    Owner *owner;
    s32 state;
    u32 flags;
    s32 start;
    Ring *ring;
    void *actor;
    s32 pending;
    s32 done;
    s32 found;
    u8 objFlags;
    void *pos;
    void *ctx;
    u32 bits;
    s32 sp20;
    void *have3;
    void *have4;
    void *have6;
    s32 count3;
    s32 count4;
    s32 count6;
    GlyphTable glyphs;

    done = 0;
    found = 0;
    first = -1;
    sp20 = -1;
    have3 = 0;
    have4 = 0;
    have6 = 0;
    count3 = 0;
    count4 = 0;
    count6 = 0;
    flags = fn_8003BD48(obj, arg);
    state = fn_80128EAC(obj);
    a = fn_801A7498(arg);
    b = fn_801A74B8(arg);
    actor = fn_80201814(a);
    objFlags = fn_80128EE4(obj);
    owner = fn_80201B8C(actor);
    ring = owner->ring;
    fn_801A74D8(arg, 0x200000);

    if ((flags & 3) && state == 4) {
        s32 pass;

        fn_80128B10(obj, 3);
        bits = fn_801290D0(obj);
        fn_80128F74(obj, bits | 0x200);
        pending = fn_80078608(actor, &sp20, &have3, &have4, &have6, &count3, &count4, &count6);
        pass = 1;
        start = ring->index;
        while (!done && !found) {
            type = ring->slots[ring->index].type;
            if (first == -1 && type != 0) {
                first = type;
            }
            switch (type) {
            case 0:
                break;
            case 3:
                if (count3 < ring->need3) {
                    found = 1;
                } else if (count3 == ring->need3 && (s32)have3 != 0 && pass == 2) {
                    found = 1;
                    pending = 0;
                    fn_8020123C(8, a, have3, arg);
                }
                break;
            case 4:
                if (count4 < ring->need4) {
                    found = 1;
                } else if (count4 == ring->need4 && (s32)have4 != 0 && pass == 2) {
                    found = 1;
                    pending = 0;
                    fn_8020123C(8, a, have4, arg);
                }
                break;
            case 6:
                if (count6 < ring->need6) {
                    found = 1;
                } else if (count6 == ring->need6 && (s32)have6 != 0 && pass == 2) {
                    found = 1;
                    pending = 0;
                    fn_8020123C(8, a, have6, arg);
                }
                break;
            }
            if (!found) {
                ring->index = (ring->index == 5) ? 0 : ring->index + 1;
                if (start == ring->index) {
                    pass++;
                    if (pass == 3) {
                        done = 1;
                    }
                }
            }
        }
        if (pending) {
            if ((s32)have3 != 0) {
                fn_8020123C(8, a, have3, arg);
            } else if ((s32)have6 != 0) {
                fn_8020123C(8, a, have6, arg);
            } else if ((s32)have4 != 0) {
                fn_8020123C(8, a, have4, arg);
            }
        }
        if (type == 0) {
            type = first;
        }
        fn_800CA3A0(actor, type, 0, 0);
        switch (type) {
        case 3:
            ring->timer = 0x2B7;
            break;
        case 6:
            ring->timer = 0x311;
            break;
        case 4:
        case 5:
            ring->timer = 0x25D;
            break;
        }
        ctx = fn_80201BC8(fn_80201814(b));
        switch (owner->mode) {
        case 1:
            fn_80120AD0(ctx, 0, 100, 0x22, lbl_8064E910, lbl_8064E914);
            break;
        case 2:
            fn_80120AD0(ctx, 0, 100, 0xA, lbl_8064E910, lbl_8064E914);
            break;
        case 3:
            fn_80120AD0(ctx, 0, 100, 0x12, lbl_8064E910, lbl_8064E914);
            break;
        }
        fn_8020123C(0x67, a, b, arg);
        fn_8020104C(0x68, a, b, 0, lbl_8064E918);
    } else if ((objFlags & 0x20) && ((flags & 0x10) || (flags & 0x40))) {
        pos = fn_8011F130(obj);
        glyphs = *(GlyphTable *)lbl_802391D0;
        fn_801AC9F4(glyphs.ids[fn_800FBFB0() % 11], 100, pos, 2);
        fn_80128B10(obj, 0xF);
        bits = fn_801290D0(obj);
        fn_80128F74(obj, bits | 0x200);
        ring->timer = 0x3C;
    }
    fn_801A74E8(arg, 0x200000);
    return 1;
}
