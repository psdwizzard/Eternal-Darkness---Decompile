typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct EventState {
    void *created;
    u8 pad04[0x90];
    u8 blocked;
} EventState;

extern void fn_80006954(int);
extern void *fn_8004914C();
extern int fn_800CC2D8(void *, int);
extern int fn_8011EB04(void *);
extern void *fn_8011F130(void *);
extern void fn_801287C4(void *, void *, u32, u32);
extern void fn_80128C28(void *, u32, u32);
extern void fn_80128C44(void *, u32, u32);
extern int fn_80129334(void *, int, int *, int);
extern int fn_80129364(void *, int, int, int *, int);
extern void *fn_801294DC(void *, int, int, int);
extern int fn_8012A1BC(void *, int);
extern int fn_8012A1FC(void *, int);
extern void fn_8012CBE8(void *, int, Vec3 *, Vec3 *, Vec3 *, int);
extern u32 fn_801578AC(void *);
extern u8 fn_8015793C(void *);
extern u16 fn_80157994(void *);
extern void *fn_801A717C(void);
extern void fn_801A7324(void *, void *);
extern u32 fn_801A7468(void *);
extern u32 fn_801A7490(void *);
extern void fn_801A74A0(void *, u32);
extern u32 fn_801A74C0(void *);
extern u32 fn_801A74C8(void *, u32);
extern void fn_801A7518(void *, s16);
extern void fn_801A7538(void *, u16);
extern void fn_801A7550(void *, u32);
extern void fn_801A7558(void *, u32);
extern u32 fn_801A7570(void *);
extern u16 fn_801A7580(void *);
extern void fn_801A75A8(void *, u8);
extern void fn_801A75B0(void *, u8);
extern void fn_801A764C(void *, void *);
extern u32 fn_801A76B0(void *);
extern void *fn_801A7778(void *);
extern u16 fn_801A77F8(void *);
extern u32 fn_801A7840(void *);
extern void *fn_80200C38(void *);
extern unsigned long long fn_8020123C(int, int, int, int);
extern int fn_80201B54(void *);
extern void *fn_80201B8C(void *);
extern void *fn_80201BC8(void *);
extern void fn_80201D14(void *, u8);
extern void fn_80201D2C(void *, int);
extern int fn_8003B8A0(void *, void *);
extern void *fn_800BF060(void *, void *);
extern void fn_800BF238(void), fn_800BF4C8(void);
extern int fn_800BF7C0(void *, void *), fn_800BF81C(void *, void *);
extern int fn_800BFF14(void *, void *), fn_800BFF84(void *, void *);
extern int fn_800C0240(void *, void *), fn_800C3A74(void *, void *);
extern void fn_800C1F54(void);
extern int fn_80204230(int, int), fn_802042A4(int, int);
extern Vec3 lbl_802478D0;
extern Vec3 lbl_802478DC;

int fn_800BF848(void *object, void *source)
{
    int mainIndex;
    int phase2Index, phase4Index, nextIndex;
    int previousIndex, otherIndex;
    Vec3 third, second, first;
    int special, blocked;
    int replace;
    u8 enabled;
    EventState **state;
    void *event, *collection, *effect;
    int action, kind;
    u32 related;
    u32 mode, flags;
    void *model, *queue, *created;
    int subtype, result;
    s16 scale;
    u8 intensity;

    special = 0;
    mainIndex = 0;
    state = (EventState **)fn_80201B8C(object);
    replace = 0;
    blocked = 0;
    event = fn_80200C38(source);
    collection = fn_80201BC8(object);
    kind = fn_80201B54(object);
    related = fn_801A7490(event);
    action = fn_801A7468(event);
    effect = fn_801A7778(event);
    mode = fn_801578AC(effect);
    flags = fn_801A74C0(event) | 1;
    if (mode == 8 && !(flags & 0x20)) special = 1;
    model = fn_8004914C(event);
    subtype = fn_8011EB04(model);
    if (subtype == 0x60 && fn_801A7580(event) < 0x3C) {
        action = 0x6F;
        replace = 1;
    }
    if ((*state)->blocked != 0) blocked = 1;
    intensity = (u8)fn_8015793C(effect);
    scale = intensity;
    if (blocked == 0 && action != -1) {
        queue = fn_801294DC(collection, action, special, 6);
        if (queue != 0) {
            created = fn_801A717C();
            fn_801A7324(event, created);
            if (effect != 0) {
                int value = (u8)fn_801A77F8(event);
                fn_801A75A8(created, value | fn_801A76B0(event));
            }
            fn_801A74A0(created, kind);
            fn_801A74C8(created, flags);
            fn_801A7538(created, 1);
            fn_801A7518(created, intensity);
            fn_801A7550(created, 12);
            fn_801A7558(created, 12);
            fn_801A75B0(created, 1);
            fn_801A764C(created, fn_8011F130(collection));

            if (mode != 0x40) {
                /* ASM: nop preserves the retail scheduling slot, which C cannot express. */
                asm { nop }
            }
            if ((mode == 0x40 || mode == 0x80) && fn_80157994(effect) >= 2)
                fn_801A75B0(created, 2);
            if (mode == 0x10) fn_801A7518(created, 0x3C);
            if (mode == 0x80) {
                fn_801A7518(created, (s16)(scale * 2));
            } else if (mode == 0x40) {
                fn_801A7518(created, (s16)(scale * 2));
            } else if (mode == 8) {
                fn_801A75B0(created, 3);
                fn_801A7518(created, (s16)(scale * 3));
            } else if (mode == 4) {
                fn_801A75B0(created, 3);
                fn_801A7518(created, (s16)(scale * 3));
            }
            if (model != 0) {
                switch (subtype) {
                case 0x70:
                case 0x71:
                case 0x7E:
                    break;
                default:
                    fn_801A74C8(created, flags | 0x1000);
                    break;
                }
            }

            previousIndex = fn_80129364(collection, 1, 0, &mainIndex, -1);
            otherIndex = fn_80129364(collection, 1, 0x10, &nextIndex, -1);
            if (previousIndex != -1) {
                fn_801287C4(queue, fn_800BF060, (u32)created, mainIndex);
                enabled = (u8)fn_800CC2D8(model, 0);
                if (fn_801A7570(created) & 0x10018) {
                    u32 phase = fn_801A7840(created);
                    if ((u8)fn_800CC2D8(model, 0)) {
                        Vec3 *pFirst = &first, *pSecond = &second, *pThird = &third;
                        first = lbl_802478D0;
                        second = first;
                        third = lbl_802478DC;
                        fn_8012CBE8(model, 0x10, pThird, pSecond, pFirst, 0);
                        fn_801287C4(queue, fn_800BFF14, (u32)created, mainIndex - 1);
                        fn_801287C4(queue, fn_800BF4C8, (u32)created, mainIndex + 1);
                        fn_801287C4(queue, fn_800BFF84, (u32)created, mainIndex + 1);
                        fn_801287C4(queue, fn_800BF238, (u32)created, mainIndex - 1);
                    }
                    if (otherIndex != -1)
                        fn_801287C4(queue, fn_800C1F54, (u32)created, nextIndex);
                    if (replace) {
                        int a = fn_8012A1BC(collection, action);
                        fn_80006954((a - fn_8012A1FC(collection, action)) * 2);
                    } else {
                        fn_801287C4(queue, fn_800C3A74, 1,
                                    mainIndex + 0x10);
                    }
                    fn_801287C4(queue, fn_800BF81C, (u32)event, mainIndex + 1);
                    if (phase == 2) {
                        result = fn_80129334(collection, 1, &phase2Index,
                                              previousIndex);
                        if (result != -1)
                            fn_801287C4(queue, fn_800BF060, (u32)created,
                                        phase2Index);
                        fn_801287C4(queue, fn_800BF7C0, (u32)created,
                                    phase2Index + 1);
                    } else if (phase == 4) {
                        result = fn_80129334(collection, 1, &phase4Index,
                                              previousIndex);
                        if (result != -1)
                            fn_801287C4(queue, fn_800BF7C0, (u32)created,
                                        phase4Index + 1);
                    } else if (phase != 8) {
                        fn_801287C4(queue, fn_800BF7C0, (u32)created, mainIndex + 1);
                    }
                } else {
                    fn_801287C4(queue, fn_8003B8A0, (u32)created, mainIndex);
                }
            }
            if (mode != 8 || (flags & 0x20))
                fn_80128C28(queue, (u32)fn_80204230, (u32)created);
            if ((fn_801A7570(created) & 0x10018) && ((int)enabled != 0))
                fn_80128C44(queue, (u32)fn_800C0240, (u32)created);
            else
                fn_80128C44(queue, (u32)fn_802042A4, (u32)created);
            if ((int)related != 0) fn_8020123C(10, kind, related, (int)created);
            if (mode == 8) {
                fn_80201D2C(object, 0x60);
                fn_80201D14(object, 1);
            } else {
                fn_80201D2C(object, 6);
                fn_80201D14(object, 1);
            }
            (*state)->created = created;
            return 1;
        }
    }
    return 0;
}
