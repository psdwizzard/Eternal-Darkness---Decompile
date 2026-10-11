typedef unsigned short u16;
typedef int s32;
typedef float f32;

typedef struct Actor800D9814 {
    unsigned char pad00[0x54];
    void *effects[4];
    unsigned char pad64[0x20];
    u16 flags;
} Actor800D9814;

typedef struct Context800D9814 {
    unsigned char pad00[0x64];
    Actor800D9814 *actor;
} Context800D9814;

extern s32 lbl_80239978[4];
extern s32 lbl_80325850[];
extern f32 lbl_8064F458;
extern Context800D9814 *fn_80201B8C(s32, s32, s32, s32, s32 *);
extern s32 fn_80201B54(s32);
extern void fn_80201B94(s32);
extern s32 fn_80201C48(void);
extern void *fn_801D62D0(s32, s32, s32, s32, s32, s32, s32, s32,
                         s32, s32, s32, s32, s32, s32, s32, s32,
                         s32, s32, s32, s32, s32, s32, s32, s32,
                         s32, s32);
extern void fn_80031A00(s32, s32 *, s32, void *, s32, s32, s32, s32,
                        s32, s32, s32);
extern void fn_8020104C(s32, s32, s32, s32, f32);
extern void fn_801AC9F4(s32, s32, void *, s32);

s32 fn_800D9814(s32 unused, s32 object)
{
    Context800D9814 *context;
    Actor800D9814 *actor;
    s32 renderContext;
    s32 active;
    s32 i;
    s32 ids[4];

    ids[0] = lbl_80239978[0];
    ids[1] = lbl_80239978[1];
    ids[2] = lbl_80239978[2];
    ids[3] = lbl_80239978[3];
    context = fn_80201B8C(object, lbl_80239978[2], lbl_80239978[1],
                          lbl_80239978[0], lbl_80239978);
    actor = context->actor;
    renderContext = fn_80201B54(object);
    fn_80201B94(object);
    active = fn_80201C48();

    if (active != 0 && (actor->flags & 0x10) != 0) {
        for (i = 0; i < 4; i++) {
            actor->effects[i] = fn_801D62D0(renderContext, ids[i], 1,
                                             active, 0, 0, 3, 1,
                                             1, 0, 0x20, 0x10, 0xA, 3, 0, 1,
                                             0x11, 0xA, 0xA, 0x28, 3, 1,
                                             -1, 0x40040,
                                             0x2030, 0xC);
        }
    } else if (active != 0) {
        for (i = 0; i < 4; i++) {
            fn_80031A00(2, (s32 *)((char *)lbl_80325850 + i * 0xC4), 3,
                        (void *)((char *)actor + 0x78), renderContext,
                        ids[i], 1, 0x20, 0x10, 0, 1);
        }
        actor->flags |= 0x400;
        fn_8020104C(0xE0, renderContext, renderContext, 0, lbl_8064F458);
    }
    fn_801AC9F4(0x25B, 0x64, (void *)((char *)actor + 0xAC), 2);
    return 1;
}
