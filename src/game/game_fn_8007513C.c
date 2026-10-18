typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;

#define NULL ((void *)0)

typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

/* Per-instance AI work area (owner->0x44). */
typedef struct AiWork {
    /* 0x000 */ f32 homeDist;
    /* 0x004 */ f32 homeDistScaled;
    /* 0x008 */ u8 unk8[0xC8 - 0x8];
    /* 0x0C8 */ u32 unkC8;
    /* 0x0CC */ u8 unkCC[0x190 - 0xCC];
    /* 0x190 */ Vec3 homePos;
    /* 0x19C */ u8 unk19C[0x1B4 - 0x19C];
    /* 0x1B4 */ s32 effect;
    /* 0x1B8 */ u16 timer;
    /* 0x1BA */ u16 cooldown;
    /* 0x1BC */ s8 unk1BC;
    /* 0x1BD */ s8 unk1BD;
    /* 0x1BE */ s8 unk1BE;
    /* 0x1BF */ u8 waitCount;
    /* 0x1C0 */ u8 unk1C0;
    /* 0x1C1 */ u8 hitCount;
    /* 0x1C2 */ u8 unk1C2;
    /* 0x1C3 */ u8 unk1C3;
    /* 0x1C4 */ u8 unk1C4;
    /* 0x1C5 */ u8 unk1C5;
    /* 0x1C6 */ u8 unk1C6;
} AiWork;

typedef struct AiActor {
    /* 0x00 */ u8 unk0[0x48];
    /* 0x48 */ s32 target;
    /* 0x4C */ u8 unk4C[0x94 - 0x4C];
    /* 0x94 */ Vec3 targetPos;
} AiActor;

typedef struct AiOwner {
    /* 0x00 */ u8 unk0[0x44];
    /* 0x44 */ AiWork *work;
    /* 0x48 */ u8 unk48[0x8C - 0x48];
    /* 0x8C */ AiActor *actor;
} AiOwner;

extern s32 fn_80035628(void *);
extern s32 fn_800359A0(void *, s32);
extern s32 fn_80035FB8(void *, char *, char *, char *, char *, char *);
extern u32 fn_80036D5C(void *);
extern s32 fn_8003C04C(void *);
extern void fn_8003C114(void *, void *, s32);
extern void fn_8003E5DC(void *, void *, s32, AiActor *);
extern s32 fn_800460EC(void);
extern void fn_80064B38(void *, void *, u32 *);
extern s32 fn_800654F8(s32);
extern void fn_80066754(void *, void *, u32 *);
extern void fn_80066888(void *, s32, f32, f32);
extern void fn_80066A0C(void *, void *);
extern s32 fn_80066D04(void *, s32);
extern void fn_80067180(void *);
extern void fn_800674E4(void *, void *);
extern void fn_80067650(void *, void *);
extern void fn_80068994(void *, void *);
extern s32 fn_8006D344(void *, s32, s32);
extern void *fn_8006D444(void *);
extern s32 fn_8007381C(void *, void *, void *);
extern s32 fn_80073C64(void *, void *, void *);
extern s32 fn_80074310(void *, Vec3 *, AiWork *, Vec3 *);
extern void fn_80074580(void *, void *, Vec3 *, AiWork *, Vec3 *);
extern void fn_80074990(void *, void *, s32, AiActor *, void *);
extern void fn_80074CB4(void *, void *, s32, AiActor *, void *);
extern void fn_80077704(void *);
extern void fn_8007780C(void *, AiWork *);
extern void fn_8007802C(void *, void *, AiWork *);
extern void fn_8007827C(void *, AiActor *, AiWork *);
extern void fn_80078310(void *, s32, s32, void *, void *, u32 *);
extern void fn_800777B0();
extern void fn_8007785C();
extern void fn_800781E8();
extern void fn_800783F0();
extern void fn_800784DC();
extern void fn_80078500();
extern void fn_800BD194(void *, AiActor *);
extern void fn_800BDEE4(void *, AiActor *);
extern void fn_800BE010(void *, AiActor *);
extern void fn_800BE8D4(s32);
extern u32 fn_800C9BA8(void *, AiOwner *);
extern void fn_800C9E50(void *);
extern void fn_800CA1BC(void *, void *, void *, u32 *);
extern void fn_800CA2C8(void *);
extern s32 fn_800CAF7C(void *);
extern void fn_800CC4DC(void *);
extern void fn_800CC860(void *, s32, s32);
extern void fn_800CD094(void *, void *, s32);
extern void fn_800CF598(void *);
extern void fn_800EA0FC(void *, AiActor *, s32, void *, u32 *);
extern void fn_800EA3A0(void *, AiActor *);
extern u32 rand(void);
extern void fn_8011F0E8(void *, Vec3 *);
extern void fn_8011F114(Vec3 *, void *);
extern void fn_8011FA8C(void *, s32, s32);
extern u32 fn_8011FAEC(void *);
extern void fn_8011FE64(void *, void (*)());
extern s32 fn_8011FF38(void);
extern void fn_80120AD0(void *, s32, s32, s32, f32, f32);
extern void fn_801287C4(void *, void (*)(), void *, s32);
extern void fn_80128A84(s32, s32, s32);
extern void fn_80128B34(void *, char *);
extern void fn_80128BE4(void *);
extern void fn_80128C28(void *, void (*)(), s32);
extern void fn_80128C44(void *, void (*)(), s32);
extern s32 fn_80128E30(void *);
extern s32 fn_80128EAC(void *);
extern u32 fn_80128EE4(void *);
extern s32 fn_80128F40(void *);
extern void fn_80128F74(void *, s32);
extern s32 fn_801290D0(void *);
extern void *fn_801294DC(void *, s32, s32, s32);
extern void fn_8012998C(void *, f32);
extern void fn_80129A00(void *, s32, s32, f32, f32);
extern void fn_80129BA4(void *, f32, f32);
extern void fn_80129FD0(void *, s32, s32);
extern s32 fn_8012A1BC(void *, s32);
extern s32 fn_8012A1FC(void *, s32);
extern s32 fn_8012AFC4(void *);
extern void fn_8012B324(void *);
extern void fn_8012B344(void *);
extern f32 fn_8012B750(void *);
extern f32 fn_8012B7D0(void *, Vec3 *);
extern void fn_8012C62C(void *, s32, u32 *, u32 *, u32 *, s32);
extern void fn_8012CBE8(void *, s32, Vec3 *, Vec3 *, Vec3 *, s32);
extern void fn_8012FE10(void *, s32, Vec3 *);
extern void fn_8013009C(void *, Vec3 *);
extern s32 fn_80130108(void *);
extern void fn_80137ED0(s32);
extern Vec3 *fn_80137FB8(s32);
extern void fn_80153FD0(s32, void *);
extern u32 fn_80178E94(Vec3 *, Vec3 *);
extern void fn_8017A12C(f32 *, f32, f32);
extern void fn_801A7228(s32);
extern u32 fn_801A74C0(s32);
extern u32 fn_801A7570(s32);
extern void fn_801A977C(void *, s32);
extern void fn_801AAE68(s32, s32, s32, f32, Vec3 *, s32, s32, s32, u16, s32);
extern void fn_801AC9F4(u16, s32, Vec3 *, s32);
extern void fn_801E7DCC(char *, ...);
extern void fn_801E8328(s32, void *);
extern void fn_802006D4(s32, s32, s32, s32, s32);
extern s32 fn_80200C10(void *);
extern s32 fn_80200C20(void *);
extern s32 fn_80200C28(void *);
extern s32 fn_80200C38(void *);
extern void fn_8020104C(s32, s32, s32, s32, f32);
extern u64 fn_802011D4(void *);
extern u64 fn_8020123C(s32, s32, s32, s32);
extern void *fn_80201814(s32);
extern s32 fn_80201B44(void);
extern s32 fn_80201B54(void *);
extern s32 fn_80201B5C(void *);
extern AiOwner *fn_80201B8C(void *);
extern s32 fn_80201B94(void *);
extern void *fn_80201B9C(void);
extern void *fn_80201BC8(void *);
extern s32 fn_80201C48(s32);
extern void fn_80201D14(void *, s32);
extern void fn_80201D1C(void *, s32);
extern void fn_80201D2C(void *, s32);
extern void fn_80201D34(void *, s32);
extern void fn_80201DD8(s32, s32);
extern s32 fn_80201EB8(void *);
extern u8 fn_80204578(void *, Vec3 *);
extern void fn_802045AC(void *, Vec3 *);
extern void fn_80204810();
extern void *fn_80204844(void *, s32);
extern void fn_80204FDC(void *);

extern Vec3 lbl_80239188[];
extern char lbl_802446C0[];
extern char lbl_8064B548[8];
extern char lbl_8064B550[8];
extern char lbl_8064B558[8];
extern char lbl_8064B560[4];
extern char lbl_8064B564[4];
extern s32 lbl_8064D18C;
extern s32 lbl_8064D5A8;
/* .sdata2 constants */
extern const f32 lbl_8064E870;
extern const f32 lbl_8064E878;
extern const f32 lbl_8064E894;
extern const f32 lbl_8064E8A0;
extern const u32 lbl_8064E8B0;
extern const u32 lbl_8064E8B4;
extern const u32 lbl_8064E8B8;
extern const u32 lbl_8064E8BC;
extern const u32 lbl_8064E8C0;
extern const f32 lbl_8064E8C4;
extern const f32 lbl_8064E8C8;
extern const f32 lbl_8064E8CC;
extern const f32 lbl_8064E8D0;
extern const f32 lbl_8064E8D4;
extern const f32 lbl_8064E8D8;
extern const f32 lbl_8064E8DC;
extern const f32 lbl_8064E8E0;
extern const f32 lbl_8064E8E4;
extern const f32 lbl_8064E8E8;
extern const f32 lbl_8064E8EC;
extern u32 lbl_80651998;

#define SET_STATE(ctx, s) \
    fn_80201D2C((ctx), (s)); \
    fn_80201D14((ctx), 1)

s32 fn_8007513C(void *ctx, s32 state, void *event, u32 *out) {
    Vec3 *paths = lbl_80239188;
    char *strings = lbl_802446C0;
    s32 kind;
    void *obj;
    AiOwner *owner;
    AiWork *work;
    AiActor *actor;
    s32 link;
    s32 id;
    s32 linked;
    void *menu;
    f32 turn;
    Vec3 pos;
    Vec3 searchPos;
    Vec3 effectPos;
    Vec3 targetPos;
    Vec3 aim;
    Vec3 newPos;
    Vec3 aimPos;
    Vec3 path2;
    Vec3 path1;
    Vec3 path0;
    Vec3 newPos2;
    f32 angle;
    f32 angle2;
    u32 colA0;
    u32 colA1;
    u32 colA2;
    u32 colB0;
    u32 colB1;
    u32 colB2;

    kind = fn_80200C10(event);
    obj = fn_80201BC8(ctx);
    owner = fn_80201B8C(ctx);
    work = owner->work;
    actor = owner->actor;
    link = fn_80201B94(ctx);
    id = fn_80201B54(ctx);
    fn_8011F114(&pos, obj);
    linked = fn_80201C48(link);

    if (kind == 3) {
        fn_800CC4DC(ctx);
        work->timer++;
        if (work->timer > 240) {
            work->hitCount = 0;
            work->timer = 0;
        }
        if (work->cooldown != 0) {
            work->cooldown--;
        }
    }

    if (state == 0) {
        if (kind == 1) {
            if (lbl_8064D18C == fn_80201EB8(ctx) && fn_80035628(ctx) == 3) {
                fn_8020104C(0x83, id, id, 0, lbl_8064E8C4);
            }
            fn_8011FE64(obj, fn_800781E8);
            work->timer = 0;
            work->hitCount = 0;
            if (work->unk1BE != 0) {
                menu = fn_801294DC(obj, 0x11, 0x20, 9);
                if (menu != NULL) {
                    colA2 = lbl_8064E8B8;
                    colA1 = lbl_8064E8B4;
                    colA0 = lbl_8064E8B0;
                    fn_8012C62C(obj, 0xF, &colA0, &colA1, &colA2, 4);
                    fn_80128C28(menu, fn_80204810, (id << 8) | 0x77);
                    fn_80128C44(menu, fn_80204810, (id << 8) | 0x77);
                    SET_STATE(ctx, 0x37);
                }
            } else {
                SET_STATE(ctx, 1);
            }
            return 1;
        } else if (kind == 8) {
            if (work->effect != -1) {
                fn_80137ED0(work->effect);
                work->effect = -1;
            }
            fn_800CD094(ctx, event, 800);
            return 1;
        } else if (kind == 0xEA) {
            fn_800674E4(ctx, event);
            return 1;
        } else if (kind == 0xEB) {
            fn_80067650(ctx, event);
            return 1;
        } else if (kind == 0xC9) {
            if (fn_8011FF38() != 0) {
                fn_8011FA8C(obj, 0, 0x20000000);
                fn_801AAE68(0x1F1, 0x64, 0, lbl_8064E8C8, &pos, 2, 2, 0, (u16)lbl_8064D18C, 0);
            }
            return 1;
        } else if (kind == 0xED) {
            fn_8020123C(0xB, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        } else if (kind == 0x3A) {
            fn_8020123C(0x27, fn_80200C20(event), fn_80200C28(event), fn_80200C38(event));
            fn_801A7228(fn_80200C38(event));
            return 1;
        } else if (kind == 0xF7) {
            work->unk1C5 = 1;
            return 1;
        } else if (kind == 0xB) {
            s32 result = 0;
            u32 flags = fn_801A7570(fn_80200C38(event));
            if (fn_8006D344(fn_8006D444(fn_80204844(fn_80201B9C(), 0x20)), 0x80000, 0) != 0) {
                fn_80067180(ctx);
                result = 1;
            } else {
                if (linked != 0 && (flags & 0x18) && work->hitCount >= 3) {
                    fn_8020104C(0x97, id, id, 0x13A, lbl_8064E8CC);
                }
                if (work->unk1C4 != 0) {
                    if (!(flags & 0x20)) {
                        fn_8020104C(0x97, id, id, 0x13A, lbl_8064E8CC);
                    }
                    work->unk1C4 = 0;
                } else {
                    result = fn_800654F8(fn_80200C38(event));
                }
            }
            if (out != NULL) {
                *out = result;
            }
            return 1;
        } else if (kind == 0x97) {
            u16 sound = fn_80200C38(event);
            s32 volume = 0x64;
            if (sound == 0x13A) {
                volume = 0x7F;
            }
            fn_801AC9F4(sound, volume, &pos, 2);
            return 1;
        } else if (kind == 0xE) {
            fn_80068994(ctx, event);
            return 1;
        } else if (kind == 0x27) {
            fn_80064B38(ctx, event, out);
            return 1;
        } else if (kind == 0x3B) {
            if (out != NULL) {
                *out = 1;
            }
            return 1;
        } else if (kind == 0x82) {
            if (out != NULL) {
                *out = 0;
            }
            return 1;
        } else if (kind == 0xA) {
            if (linked != 0) {
                fn_80200C38(event);
                fn_8007802C(ctx, event, work);
            }
            return 1;
        } else if (kind == 0x3D) {
            fn_8007827C(ctx, actor, work);
            fn_80201DD8(link, 0);
            return 1;
        } else if (kind == 0x3E) {
            fn_800BD194(ctx, actor);
            fn_800C9E50(ctx);
            if (fn_80035628(ctx) == 3 && lbl_8064D18C == fn_80201EB8(ctx) && work->unkC8 == 0) {
                fn_8020104C(0x83, id, id, 0, lbl_8064E8C4);
            }
            return 1;
        } else if (kind == 0x83) {
            if (lbl_8064D18C == fn_80201EB8(ctx) && fn_80035628(ctx) == 3) {
                fn_80153FD0(id, work->unk8);
            }
            return 1;
        } else if (kind == 0x39) {
            fn_8012B324(obj);
            if (work->effect != -1) {
                fn_80137ED0(work->effect);
                work->effect = -1;
            }
            fn_800EA3A0(ctx, actor);
            fn_80201D34(ctx, 0);
            fn_80201D1C(ctx, 1);
            fn_801E8328(2, ctx);
            return 1;
        } else if (kind == 0x32) {
            fn_80066A0C(ctx, event);
            return 1;
        } else if (kind == 0x35) {
            fn_80066754(ctx, event, out);
            return 1;
        } else if (kind == 0xE6) {
            fn_80066754(ctx, event, out);
            return 1;
        } else if (kind == 0xF3) {
            s32 item = fn_80200C38(event);
            fn_800EA0FC(ctx, actor, item, event, out);
            return 1;
        }
    } else if (state == 1) {
        if (kind == 3) {
            if (!(lbl_8064D5A8 & 7) && fn_800359A0(ctx, 0) != 0) {
                u32 flags = fn_80036D5C(fn_80201814(fn_80201C48(link)));
                if ((flags & 0x80) || (flags & 0x8000)) {
                    fn_80201DD8(link, 0);
                } else {
                    SET_STATE(ctx, 0x2D);
                }
            }
            return 1;
        } else if (kind == 0x5A) {
            void *other = fn_80201814(fn_80200C20(event));
            void *target;
            if (other != NULL) {
                target = fn_80201BC8(other);
            } else {
                target = NULL;
            }
            if (linked == 0 && target != NULL && fn_800460EC() == 0 && fn_800CAF7C(ctx) != 0) {
                fn_8011F114(&targetPos, target);
                actor->targetPos = targetPos;
                SET_STATE(ctx, 0x15);
            }
            return 1;
        }
    } else if (state == 0x15) {
        if (kind == 1) {
            fn_8012B344(obj);
            return 1;
        } else if (kind == 3) {
            aim = actor->targetPos;
            turn = fn_8012B7D0(obj, &aim);
            fn_8017A12C(&angle, fn_8012B750(obj), turn);
            {
                f32 a = angle;
                if (a < lbl_8064E870) {
                    a = -a;
                }
                if (a > lbl_8064E8A0 && fn_8012AFC4(obj) == 0) {
                    fn_80129A00(obj, 2, 5, turn, lbl_8064E8D0);
                } else if (fn_8012AFC4(obj) != 0) {
                    fn_8012998C(obj, turn);
                } else {
                    SET_STATE(ctx, 1);
                }
            }
            return 1;
        } else if (kind == 0x5A) {
            void *other = fn_80201814(fn_80200C20(event));
            void *target;
            if (other != NULL) {
                target = fn_80201BC8(other);
            } else {
                target = NULL;
            }
            if (target != NULL && fn_800460EC() == 0 && fn_800CAF7C(ctx) != 0) {
                fn_8011F114(&newPos, target);
                actor->targetPos = newPos;
            }
            return 1;
        } else if (kind == 2) {
            s32 mode = fn_80128EAC(obj);
            s32 flags = fn_801290D0(obj);
            if ((flags & 4) && (mode == 3 || mode == 2)) {
                fn_80128F74(obj, flags & ~4);
            }
            return 1;
        }
    } else if (state == 0x2D) {
        if (kind == 1) {
            work->waitCount = rand() & 0x1E;
            fn_80077704(ctx);
            fn_802045AC(ctx, &searchPos);
            work->homeDist = fn_80178E94(&pos, &searchPos);
            return 1;
        } else if (kind == 0x3D) {
            SET_STATE(ctx, 1);
            if (out != NULL) {
                *out = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        } else if (kind == 3) {
            if (fn_80066D04(ctx, 0) == 0) {
                SET_STATE(ctx, 1);
            }
            if (!(lbl_8064D5A8 & 7)) {
                fn_800359A0(ctx, 0);
            }
            if (linked != 0) {
                u32 dist;
                void *target;
                s32 near;
                fn_802045AC(ctx, &searchPos);
                dist = fn_80178E94(&pos, &searchPos);
                near = dist < 225;
                target = fn_80201BC8(fn_80201814(linked));
                if (work->waitCount != 0) {
                    work->waitCount--;
                }
                if (near && fn_80204578(ctx, &searchPos) && work->waitCount == 0 && work->unk1C0 == 0) {
                    if (fn_8007381C(ctx, obj, event) == 0) {
                        SET_STATE(ctx, 1);
                    }
                } else if (fn_80130108(obj) != 0) {
                    fn_8012FE10(target, 0, &searchPos);
                    fn_8013009C(obj, &searchPos);
                    aimPos = searchPos;
                    turn = fn_8012B7D0(obj, &aimPos);
                    fn_8017A12C(&angle, fn_8012B750(obj), turn);
                    {
                        f32 a = angle;
                        if (a < lbl_8064E870) {
                            a = -a;
                        }
                        if (a > lbl_8064E8D4 && fn_8012AFC4(obj) == 0) {
                            fn_80129A00(obj, 2, 5, turn, lbl_8064E8D0);
                        }
                    }
                } else {
                    s32 bit = (fn_80128EE4(target) >> 3) & 1;
                    if (dist > (s32)work->homeDist + 200 && bit != 0) {
                        if (fn_80201C48(link) != 0) {
                            fn_800BDEE4(ctx, owner->actor);
                        }
                        SET_STATE(ctx, 3);
                    } else if (dist > 800) {
                        SET_STATE(ctx, 0x2C);
                    } else if (fn_80073C64(ctx, obj, event) == 0) {
                        SET_STATE(ctx, 0x2C);
                    }
                }
            } else {
                SET_STATE(ctx, 1);
            }
            return 1;
        } else if (kind == 2) {
            fn_8011FE64(obj, fn_800781E8);
            return 1;
        }
    } else if (state == 0x2C) {
        if (kind == 1) {
            work->waitCount = rand() & 0x1E;
            work->homePos = pos;
            fn_802045AC(ctx, &searchPos);
            work->homeDist = fn_80178E94(&pos, &searchPos);
            work->homeDistScaled = work->homeDist * lbl_8064E894;
            return 1;
        } else if (kind == 3) {
            fn_800BE010(ctx, actor);
            if (fn_80201C48(link) != 0) {
                fn_800BDEE4(ctx, actor);
            }
            fn_80074CB4(ctx, obj, id, actor, event);
            return 1;
        } else if (kind == 2) {
            if (fn_8012AFC4(obj) != 0) {
                fn_8012B344(obj);
            }
            return 1;
        }
    } else if (state == 3) {
        if (kind == 3) {
            fn_800BE010(ctx, actor);
            if (fn_80201C48(link) != 0) {
                fn_800BDEE4(ctx, actor);
            }
            fn_80074990(ctx, obj, id, actor, event);
            return 1;
        }
    } else if (state == 6) {
        if (kind == 0xC) {
            SET_STATE(ctx, 1);
            return 1;
        } else if (kind == 7) {
            if (fn_80035FB8(ctx, strings + 0x6C, lbl_8064B548, strings + 0x84, lbl_8064B550, strings + 0x90) == 0) {
                SET_STATE(ctx, 1);
            }
            return 1;
        } else if (kind == 0xD) {
            SET_STATE(ctx, 1);
            fn_8012B344(obj);
            return 1;
        }
    } else if (state == 0x33) {
        if (kind == 1) {
            work->unk1BC = 0;
            work->unk1BD = 0;
            work->unk1C2 = 0;
            work->unk1C3 = 0;
            work->unk1C5 = 0;
            work->effect = -1;
            work->unk1C6 = 0;
            return 1;
        } else if (kind == 3) {
            if (work->unk1C3 != 0) {
                if (fn_8011FAEC(obj) & 0x30) {
                    fn_8020123C(0x74, id, id, 0);
                } else {
                    fn_80074580(obj, fn_80201BC8(fn_80201814(actor->target)), &pos, work, &effectPos);
                    if (fn_80074310(obj, &pos, work, &effectPos) == 0) {
                        work->unk1C3 = 0;
                    }
                }
            }
            return 1;
        } else if (kind == 0x3B) {
            s32 level = fn_80128F40(obj);
            void *other = fn_80201814(fn_80200C20(event));
            if (actor->target != fn_80201B44() || (level >> 17) < 0x29 ||
                (other != NULL && fn_80201B5C(other) == 0x19)) {
                if (out != NULL) {
                    *out = 1;
                }
            } else if (out != NULL) {
                *out = 0;
            }
            return 1;
        } else if (kind == 0xEF) {
            if (out != NULL) {
                *out = 1;
            }
            return 1;
        } else if (kind == 0x6C) {
            if (work->unk1BC != 0) {
                fn_8020123C(0x6D, id, id, 0);
            } else {
                menu = fn_801294DC(obj, 9, 0x20, 9);
                if (menu != NULL) {
                    fn_8020123C(0x75, id, actor->target, 0);
                    colB2 = lbl_80651998;
                    colB1 = lbl_8064E8C0;
                    colB0 = lbl_8064E8BC;
                    fn_8012C62C(obj, 0xF, &colB0, &colB1, &colB2, 4);
                    path0 = paths[4];
                    path1 = paths[3];
                    path2 = paths[2];
                    fn_8012CBE8(obj, 0xF, &path2, &path1, &path0, 0);
                    fn_801287C4(menu, fn_800777B0, ctx, 0x28);
                    fn_80128C28(menu, fn_80204810, (id << 8) | 0x39);
                    fn_80128C44(menu, fn_80204810, (id << 8) | 0x39);
                    if (work->effect != -1) {
                        fn_80137ED0(work->effect);
                        work->effect = -1;
                    }
                    SET_STATE(ctx, 0x63);
                }
            }
            return 1;
        } else if (kind == 0x74) {
            fn_8012B344(obj);
            return 1;
        } else if (kind == 7) {
            if (work->unk1C6 != 0 && work->effect != -1) {
                Vec3 *effectPosPtr = fn_80137FB8(work->effect);
                fn_8011F0E8(obj, effectPosPtr);
                fn_80137ED0(work->effect);
                work->effect = -1;
                work->unk1C6 = 0;
                fn_8011FA8C(obj, 0, 0xC0);
                SET_STATE(ctx, 1);
            } else if (work->unk1BD != 0 && work->unk1C5 == 0) {
                fn_8020123C(0x6D, id, id, 1);
                fn_8020123C(0x74, id, actor->target, 0);
                actor->target = 0;
                work->unk1C2 = 0;
            } else if (work->unk1C2 != 0 && work->unk1C5 == 0) {
                menu = fn_801294DC(obj, 0xF, 0, 6);
                if (menu != NULL) {
                    fn_80128B34(obj, strings + 0x60);
                    fn_801287C4(menu, fn_8007785C, NULL, 3);
                    fn_80128C28(menu, fn_80204810, (id << 8) | 6);
                    fn_80128C44(menu, fn_80204810, (id << 8) | 6);
                    SET_STATE(ctx, 0x62);
                } else {
                    SET_STATE(ctx, 1);
                }
                fn_8020123C(0x74, id, actor->target, 0);
                actor->target = 0;
                work->unk1C2 = 0;
                if (work->effect != -1) {
                    fn_80137ED0(work->effect);
                    work->effect = -1;
                }
            } else if (!(fn_8011FAEC(obj) & 0x40)) {
                u32 holder = fn_8020123C(0xD9, id, actor->target, 0) & 0xFFFFFFFF;
                if (holder == id) {
                    fn_8020123C(0x74, id, actor->target, 0);
                }
                fn_8020123C(0x6D, id, id, 1);
                actor->target = 0;
            } else {
                u32 holder = fn_8020123C(0xD9, id, actor->target, 0) & 0xFFFFFFFF;
                if (holder == id) {
                    fn_8020123C(0x74, id, actor->target, 0);
                }
                actor->target = 0;
                if (work->effect != -1) {
                    fn_80137ED0(work->effect);
                    work->effect = -1;
                }
                if (fn_80035FB8(ctx, strings + 0x6C, strings + 0xA8, strings + 0x84, lbl_8064B550, strings + 0x90) == 0) {
                    SET_STATE(ctx, 1);
                }
            }
            return 1;
        } else if (kind == 0x70) {
            work->unk1BC = 1;
            return 1;
        } else if (kind == 0x6D) {
            s32 flip = fn_80200C38(event);
            menu = fn_801294DC(obj, 0x4C, 0x120, 8);
            if (menu != NULL) {
                s32 top = fn_8012A1FC(obj, 0x4C);
                s32 bottom = fn_8012A1BC(obj, 0x4C);
                s32 row = top + 0x12;
                s32 tag;
                if (flip != 0) {
                    fn_80129FD0(obj, (top + 0x10) << 17, 1);
                }
                fn_801287C4(menu, fn_800783F0, ctx, row);
                fn_801287C4(menu, fn_800784DC, ctx, 0x89);
                fn_801287C4(menu, fn_80078500, ctx, bottom - 6);
                tag = id << 8;
                fn_80128C28(menu, fn_80204810, tag | 0x76);
                fn_80128C44(menu, fn_80204810, tag | 7);
                newPos2 = *fn_80137FB8(work->effect);
                turn = lbl_8064E8D8 + fn_8012B7D0(obj, &newPos2);
                fn_8017A12C(&angle2, fn_8012B750(obj), turn);
                fn_80129BA4(menu, turn, lbl_8064E878);
                SET_STATE(ctx, 0x36);
            } else {
                actor->target = 0;
                SET_STATE(ctx, 1);
            }
            return 1;
        } else if (kind == 0x73) {
            fn_8012B344(obj);
            fn_8011FA8C(obj, 0, 0xC0);
            actor->target = 0;
            return 1;
        } else if (kind == 0x3D) {
            work->unk1C6 = 1;
            fn_8020123C(0x74, id, actor->target, 0);
            fn_8020123C(0x74, id, id, 0);
            if (out != NULL) {
                *out = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        } else if (kind == 0x35) {
            fn_80078310(ctx, id, actor->target, obj, event, out);
            return 1;
        } else if (kind == 0xE6) {
            fn_80078310(ctx, id, actor->target, obj, event, out);
            return 1;
        } else if (kind == 0x32) {
            fn_8020123C(0x74, id, actor->target, 0);
            fn_8020123C(0x74, id, id, 0);
            if (out != NULL) {
                *out = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        } else if (kind == 8) {
            fn_8020123C(0x74, id, actor->target, 0);
            fn_800CD094(ctx, event, 800);
            return 1;
        } else if (kind == 0x39) {
            fn_8020123C(0x74, id, actor->target, 0);
            fn_80201D34(ctx, 0);
            fn_80201D1C(ctx, 1);
            fn_801E8328(2, ctx);
            return 1;
        } else if (kind == 0xA) {
            return 1;
        }
    } else if (state == 0x36) {
        if (kind == 1) {
            work->unk1C6 = 0;
            return 1;
        } else if (kind == 0x3D) {
            work->unk1C6 = 1;
            fn_8012B344(obj);
            if (out != NULL) {
                *out = fn_802011D4(event) & 0xFFFFFFFF;
            }
            return 1;
        } else if (kind == 0x76) {
            fn_80128BE4(obj);
            fn_8007780C(obj, work);
            SET_STATE(ctx, 1);
            actor->target = 0;
            return 1;
        } else if (kind == 0xEF) {
            if (out != NULL) {
                *out = 1;
            }
            return 1;
        } else if (kind == 7) {
            fn_80128BE4(obj);
            if (work->unk1C6 != 0 && work->effect != -1) {
                Vec3 *effectPosPtr = fn_80137FB8(work->effect);
                fn_8011F0E8(obj, effectPosPtr);
                fn_80137ED0(work->effect);
                work->effect = -1;
                work->unk1C6 = 0;
                fn_8011FA8C(obj, 0, 0xC0);
            }
            if (fn_80035FB8(ctx, strings + 0x6C, strings + 0xB4, strings + 0x84, lbl_8064B550, strings + 0x90) == 0) {
                SET_STATE(ctx, 1);
            }
            fn_8007780C(obj, work);
            actor->target = 0;
            return 1;
        } else if (kind == 0x35) {
            return 1;
        } else if (kind == 0xE6) {
            return 1;
        } else if (kind == 0xB) {
            return 1;
        } else if (kind == 0x3B) {
            return 1;
        } else if (kind == 0x32) {
            return 1;
        } else if (kind == 0x37) {
            return 1;
        } else if (kind == 0xA) {
            return 1;
        }
    } else if (state == 0x63) {
        if (kind == 0xEF) {
            if (out != NULL) {
                *out = 1;
            }
            return 1;
        } else if (kind == 0x3B) {
            if (out != NULL) {
                *out = 0;
            }
            return 1;
        } else if (kind == 0xEF) {
            if (out != NULL) {
                *out = 1;
            }
            return 1;
        } else if (kind == 0x3D) {
            fn_8020123C(0x6E, id, actor->target, 0);
            fn_8007827C(ctx, actor, work);
            fn_8012B344(obj);
            return 1;
        } else if (kind == 0x1E) {
            return 1;
        } else if (kind == 0x35) {
            return 1;
        } else if (kind == 0xE6) {
            return 1;
        } else if (kind == 0x37) {
            return 1;
        } else if (kind == 8) {
            return 1;
        } else if (kind == 0xB) {
            return 1;
        } else if (kind == 0x27) {
            return 1;
        } else if (kind == 0xA) {
            return 1;
        }
    } else if (state == 0x37) {
        if (kind == 0x77) {
            work->unk1BE = 0;
            fn_8011FA8C(obj, 0, 0xC0);
            SET_STATE(ctx, 1);
            return 1;
        } else if (kind == 0x35) {
            return 1;
        } else if (kind == 0xA) {
            return 1;
        }
    } else if (state == 0x62) {
        if (kind == 6) {
            work->unk1BE = 0;
            SET_STATE(ctx, 1);
            return 1;
        }
    } else if (state == 0x20) {
        if (kind == 5) {
            s32 mode = fn_80128EAC(obj);
            s32 flags = fn_801290D0(obj);
            u32 item = fn_80128E30(obj);
            if (item != 0 && (mode == 0xF || mode == 0x10)) {
                fn_8012B344(obj);
                SET_STATE(ctx, 1);
            } else {
                fn_801E7DCC(strings + 0xC0, item, mode, mode == 0xF, flags, flags & 1);
                SET_STATE(ctx, 1);
            }
            return 1;
        } else if (kind == 7) {
            if (fn_80035FB8(ctx, strings + 0x120, lbl_8064B558, strings + 0x84, lbl_8064B550, strings + 0x90) == 0) {
                SET_STATE(ctx, 1);
            }
            return 1;
        } else if (kind == 0x3D) {
            fn_8007827C(ctx, actor, work);
            fn_8020123C(5, id, id, 0);
            return 1;
        } else if (kind == 2) {
            fn_802006D4(id, id, 0x20, 5, 0);
            return 1;
        } else if (kind == 0x35) {
            return 1;
        } else if (kind == 0x67) {
            return 1;
        } else if (kind == 0xA) {
            return 1;
        }
    } else if (state == 7) {
        if (kind == 0x36) {
            SET_STATE(ctx, 1);
            return 1;
        } else if (kind == 7) {
            if (fn_80035FB8(ctx, strings + 0x6C, lbl_8064B560, strings + 0x84, lbl_8064B550, strings + 0x90) == 0) {
                SET_STATE(ctx, 1);
            }
            return 1;
        }
    } else if (state == 0x1F) {
        if (kind == 1) {
            s32 mode = fn_80128EAC(obj);
            s32 slot = fn_8012A1BC(obj, mode);
            fn_80128F40(obj);
            fn_800CC860(ctx, 2, 3);
            fn_800BE8D4(id);
            fn_801A977C(obj, 0x33);
            fn_800CA2C8(ctx);
            fn_80204FDC(ctx);
            fn_8020104C(0x11, id, id, 0, lbl_8064E8DC);
            fn_80128A84(fn_80128E30(obj), 0, slot);
            return 1;
        } else if (kind == 0x30) {
            s32 result = fn_800654F8(fn_80200C38(event));
            if (out != NULL) {
                *out = result;
            }
            return 1;
        } else if (kind == 0x35) {
            fn_80066888(obj, fn_80200C38(event), lbl_8064E8E0, lbl_8064E8E4);
            return 1;
        } else if (kind == 0xE6) {
            fn_80066888(obj, fn_80200C38(event), lbl_8064E8E0, lbl_8064E8E4);
            return 1;
        } else if (kind == 0x3D) {
            fn_8007827C(ctx, actor, work);
            fn_8020123C(0x39, id, id, 0);
            return 1;
        } else if (kind == 0x11) {
            fn_800EA3A0(ctx, actor);
            fn_800CF598(ctx);
            fn_80120AD0(obj, 0, 0, 0x101, lbl_8064E8E8, lbl_8064E870);
            fn_80201D34(ctx, 0x15);
            fn_80201D1C(ctx, 1);
            return 1;
        } else if (kind == 0x31) {
            fn_8003C114(ctx, obj, id);
            return 1;
        } else if (kind == 7) {
            fn_80035FB8(ctx, strings + 0x120, strings + 0x134, strings + 0x84, strings + 0x148, strings + 0x148);
            return 1;
        } else if (kind == 0x20) {
            return 1;
        } else if (kind == 0x3B) {
            return 1;
        } else if (kind == 0x6B) {
            return 1;
        } else if (kind == 0x3F) {
            return 1;
        } else if (kind == 0x1E) {
            return 1;
        } else if (kind == 0x37) {
            return 1;
        } else if (kind == 8) {
            return 1;
        } else if (kind == 0xB) {
            return 1;
        } else if (kind == 0x27) {
            return 1;
        } else if (kind == 0x69) {
            return 1;
        } else if (kind == 0x3E) {
            return 1;
        } else if (kind == 0x67) {
            return 1;
        } else if (kind == 0xA) {
            return 1;
        }
    } else if (state == 8) {
        if (kind == 1) {
            if (obj != NULL) {
                fn_8011FA8C(obj, 0xC0, 0);
            }
            fn_800CC860(ctx, 1, 0);
            fn_800BE8D4(id);
            fn_800CA2C8(ctx);
            fn_80204FDC(ctx);
            return 1;
        } else if (kind == 3) {
            fn_8003E5DC(ctx, obj, id, actor);
            return 1;
        } else if (kind == 0x3D) {
            fn_800EA3A0(ctx, actor);
            fn_8007827C(ctx, actor, work);
            fn_8020123C(0x39, id, id, 0);
            return 1;
        } else if (kind == 0xC2) {
            fn_800CA1BC(ctx, obj, event, out);
            return 1;
        } else if (kind == 0x11) {
            if (fn_8003C04C(ctx) != 0) {
                fn_800EA3A0(ctx, actor);
                fn_800CF598(ctx);
                fn_80120AD0(obj, 0, 0, 0x101, lbl_8064E8E8, lbl_8064E870);
                fn_80201D34(ctx, 0x15);
                fn_80201D1C(ctx, 1);
            }
            return 1;
        } else if (kind == 0x33) {
            fn_8020123C(0x39, id, id, 0);
            return 1;
        } else if (kind == 0xC1) {
            if (out != NULL) {
                *out = fn_800C9BA8(obj, owner);
            }
            return 1;
        } else if (kind == 0x2F) {
            SET_STATE(ctx, 0x1F);
            return 1;
        } else if (kind == 0xB) {
            s32 item = fn_80200C38(event);
            if (fn_801A74C0(item) & 0x20) {
                s32 result = fn_800654F8(item);
                fn_8020123C(0x2F, id, id, 0);
                fn_8020104C(0x31, id, id, 0, lbl_8064E8EC);
                if (out != NULL) {
                    *out = result;
                }
            }
            return 1;
        } else if (kind == 0x35) {
            fn_80066888(obj, fn_80200C38(event), lbl_8064E8E0, lbl_8064E8E4);
            return 1;
        } else if (kind == 0xE6) {
            fn_80066888(obj, fn_80200C38(event), lbl_8064E8E0, lbl_8064E8E4);
            return 1;
        } else if (kind == 2) {
            fn_802006D4(id, id, 8, 0x11, 0);
            return 1;
        } else if (kind == 0x3B) {
            return 1;
        } else if (kind == 0x1E) {
            return 1;
        } else if (kind == 0x37) {
            return 1;
        } else if (kind == 8) {
            return 1;
        } else if (kind == 0x27) {
            return 1;
        } else if (kind == 0xA) {
            return 1;
        }
    } else if (state == 4) {
        if (kind == 1) {
            if (work->timer < 240) {
                work->hitCount++;
            } else {
                work->hitCount = 1;
            }
            work->timer = 0;
            return 1;
        } else if (kind == 0x7C) {
            fn_802045AC(ctx, &searchPos);
            if (fn_80178E94(&pos, &searchPos) > 800 || fn_80073C64(ctx, obj, event) == 0) {
                SET_STATE(ctx, 1);
            }
            return 1;
        } else if (kind == 7) {
            if (fn_80035FB8(ctx, strings + 0x6C, lbl_8064B564, strings + 0x84, lbl_8064B550, strings + 0x90) == 0) {
                SET_STATE(ctx, 1);
            }
            return 1;
        } else if (kind == 0x3B) {
            if (out != NULL) {
                *out = 0;
            }
            return 1;
        } else if (kind == 0xEF) {
            if (out != NULL) {
                *out = 1;
            }
            return 1;
        } else if (kind == 0xB) {
            if (!(fn_801A7570(fn_80200C38(event)) & 0x20)) {
                fn_8020104C(0x97, id, id, 0x13A, lbl_8064E8CC);
            }
            return 1;
        } else if (kind == 0x27) {
            return 1;
        } else if (kind == 2) {
            work->timer = 0;
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
