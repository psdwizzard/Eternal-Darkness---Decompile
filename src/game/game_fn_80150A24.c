typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef struct TargetVec3s {
    s16 x;
    s16 y;
    s16 z;
} TargetVec3s;
typedef struct TargetVec3f {
    float x;
    float y;
    float z;
} TargetVec3f;
extern s32 lbl_8064D18C;
extern const u32 lbl_8023A760[3];
extern TargetVec3s* fn_8017FDA8(void*, s32);
extern int fn_801AC9F4(s32, s32, TargetVec3f*, s32);
extern void fn_8017D700(TargetVec3s*, TargetVec3s*, s16, TargetVec3s*, s16, s16,
                        s16, s16);
extern void* fn_80201814(s32);
extern void* fn_80201890(int);
extern void* fn_80201B9C(void);
extern void* fn_80201BC8(void*);
extern void* fn_80201BC0(void*);
extern void* fn_80201B8C(u8*);
extern s32 fn_80201B4C(void*);
extern s32 fn_80201B54(s32*);
extern s32 fn_80201EB8(void*);
extern void fn_8011F114(TargetVec3f*, TargetVec3f*);
extern s32 fn_8011EB1C(void*);
extern u32 fn_80179004(TargetVec3f*, TargetVec3f*);
extern float fn_8011F6F8(void);
extern unsigned long long fn_8020123C(s32, s32, s32, s32);
extern void* fn_801A717C(void);
extern void fn_801A74A0(void*, s32);
extern void fn_801A74A8(void*, u32);
extern void fn_801A7538(void*, s32);
extern void fn_801A7518(void*, s32);
extern void fn_801A7588(void*, s32);
extern void fn_801A764C(void*, TargetVec3f*);
extern void fn_801A74D8(void*, s32);
extern void fn_801A7668(void*, u32);
extern void fn_801A7670(void*, s32);
extern void fn_801A7228(void*);
extern void fn_801D38BC(s32, u32*, s16*);
extern void fn_80152404(TargetVec3f*, s16, u16, u8, u32*);
extern void fn_80149E28(void*);
extern s32 fn_8006D548(s32, u32, u32, TargetVec3f*, u32*, u32*, s32);

void fn_80150A24(void* raw_instance)
{
    /* Declaration order preserves the retail nonvolatile-register lifetimes. */
    void* reaction;
    u32 effect_owner;
    u32 packed_owner;
    TargetVec3s* current;
    u8* instance;
    u8* work;
    s32 completed;
    void* iterator;
    s32 moved;
    s32 reacted;
    void* candidate;
    void* actor;
    u32 iterated;
    s32 radius;
    void* owner;
    s32 candidate_type;
    s32 candidate_rank;
    TargetVec3f effect_point;
    TargetVec3f origin;
    TargetVec3f point;
    TargetVec3f scratch;
    TargetVec3f fallback_point;
    s32 delta;
    u16 dx, dy, dz;

    instance = raw_instance;
    work = instance + 8;
    completed = 0;

    if ((*(u16*)(instance + 0x132C) & 3) == 0 && *(void**)(work + 0x20) != 0) {
        current = fn_8017FDA8(*(void**)(work + 0x20), 0);
        if ((*(u16*)(instance + 0x132C) & 15) == 0) {
            effect_point.x = current->x;
            effect_point.y = current->y;
            effect_point.z = current->z;
            fn_801AC9F4(0x2B4, 100, &effect_point, 2);
        }

        fn_8017D700(current, (TargetVec3s*)work, 0, (TargetVec3s*)(work + 6), 3,
                    (s16) * (u16*)(work + 12), 1, 10);
        /* Unsigned negation followed by narrowing preserves the retail
         * conditional absolute value, including the 16-bit magnitude. */
        delta = *(s16*)(work + 0) - current->x;
        dx = (u16)(delta < 0 ? -(u32)delta : (u32)delta);
        delta = *(s16*)(work + 2) - current->y;
        dy = (u16)(delta < 0 ? -(u32)delta : (u32)delta);
        delta = *(s16*)(work + 4) - current->z;
        dz = (u16)(delta < 0 ? -(u32)delta : (u32)delta);
        if ((u32)dx < 20 && (u32)dy < 20 && (u32)dz < 20) {
            actor = *(void**)(work + 0x1C);
            if (actor != 0) {
                owner = *(void**)(work + 0x14);
                iterator = fn_80201B9C();
                moved = 0;
                reacted = 0;
                radius = fn_80201890(*(s32*)(work + 0x18))
                             ? (s32)fn_8011F6F8() + 100
                             : 500;
                packed_owner = (u32)owner;
                effect_owner = (u32)owner;
                origin.x = *(s16*)(work + 0);
                origin.y = *(s16*)(work + 2);
                origin.z = *(s16*)(work + 4);
                while (iterator != 0) {
                    TargetVec3f* selected;
                    candidate = fn_80201BC8(iterator);
                    if (candidate != 0) {
                        fn_8011F114(&scratch, candidate);
                        selected = &scratch;
                    } else {
                        fallback_point = *(const TargetVec3f*)lbl_8023A760;
                        selected = &fallback_point;
                    }
                    point = *selected;
                    candidate_type = fn_80201EB8(iterator);
                    candidate_rank = fn_80201B4C(iterator);
                    if (lbl_8064D18C == candidate_type &&
                        ((u32)candidate_rank <= 1 || candidate_rank == 2) &&
                        fn_80179004(&origin, &point) < (u32)radius &&
                        fn_8011EB1C(candidate) != 4) {
                        moved = 1;
                        if ((u32)(fn_8020123C(0x3B, 0, fn_80201B54(iterator),
                                              0) &
                                  0xFFFFFFFFULL) == 1) {
                            reaction = fn_801A717C();
                            if (reaction != 0) {
                                iterated = fn_80201B54(iterator);
                                fn_801A74A0(reaction, 0);
                                fn_801A74A8(reaction, iterated);
                                fn_801A7538(reaction, 1);
                                fn_801A7518(reaction, 5);
                                fn_801A7588(reaction, 2);
                                fn_801A764C(reaction, &origin);
                                fn_801A74D8(reaction, 0x1800);
                                fn_801A7668(reaction, effect_owner);
                                fn_801A7670(reaction, 2);
                                fn_8020123C(11, 0, iterated, (s32)reaction);
                                fn_801A7228(reaction);
                                reacted = 1;
                            }
                        }
                    }
                    iterator = fn_80201BC0(iterator);
                }
                if (reacted) {
                    u32 packed;
                    u32 packed_copy;
                    s16 kind;
                    fn_801D38BC((s32)packed_owner, &packed, &kind);
                    packed_copy = packed;
                    fn_80152404(&origin, kind, radius, 4, &packed_copy);
                }
                if (moved) {
                    TargetVec3f* saved;
                    fn_8006D548(2, 0x40, 2, &origin, 0, 0, 0);
                    *(s16*)(work + 0) = origin.x;
                    *(s16*)(work + 2) = origin.y;
                    *(s16*)(work + 4) = origin.z;
                    *(u16*)(work + 12) = *(u16*)(work + 14);
                    actor = fn_80201814(*(s32*)(work + 0x18));
                    if (actor != 0) {
                        saved = (TargetVec3f*)(*(u8**)((u8*)fn_80201B8C(actor) +
                                                       0x8C) +
                                               0xA0);
                        *saved = origin;
                    }
                } else {
                    **(s32**)(work + 0x1C) = 1;
                    fn_80149E28(instance);
                    completed = 1;
                }
            }
        } else if (*(u16*)(work + 12) > 1 && (u32)dx < 500 && (u32)dy < 500 &&
                   (u32)dz < 500) {
            --*(u16*)(work + 12);
        }
    }

    if (!completed && *(void**)(work + 0x1C) == 0 &&
        *(u16*)(instance + 0x132C) >= *(u16*)(instance + 0x132E))
        fn_80149E28(instance);
}
