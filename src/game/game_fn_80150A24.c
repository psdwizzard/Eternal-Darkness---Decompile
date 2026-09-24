/* NonMatching: independent honest-C reconstruction from retail control flow. */
#include "src/game/game_targeting_types.h"

#define fn_80201B54(...) ((void *)fn_80201B54(__VA_ARGS__))

extern s32 fn_8006D548(s32, u32, u32, TargetVec3f*, u32*, u32*, s32);

void fn_80150A24(void* raw_instance)
{
    u8* instance = raw_instance;
    u8* work = instance + 8;
    TargetVec3s* current;
    void* actor;
    void* iterator;
    void* candidate;
    void* reaction;
    void* owner;
    TargetVec3f origin;
    TargetVec3f point;
    TargetVec3f scratch;
    TargetVec3f fallback_point;
    TargetVec3f effect_point;
    u16 dx, dy, dz;
    u16 radius;
    volatile s32 delta;
    s32 candidate_type;
    s32 candidate_rank;
    s32 moved;
    s32 reacted;
    s32 completed = 0;

    if ((*(u16*)(instance + 0x132C) & 3) == 0 && *(void**)(work + 0x20) != 0) {
        current = fn_8017FDA8(*(void**)(work + 0x20), 0);
        if ((*(u16*)(instance + 0x132C) & 15) == 0) {
            effect_point.x = current->x;
            effect_point.y = current->y;
            effect_point.z = current->z;
            fn_801AC9F4(0x2B4, 100, &effect_point, 2);
        }

        fn_8017D700(current, work, 0, work + 6, 3,
                    *(s16*)(work + 12), 1, 10);
        delta = *(s16*)(work + 0) - current->x;
        if (delta < 0)
            delta = -delta;
        dx = delta;
        delta = *(s16*)(work + 2) - current->y;
        if (delta < 0)
            delta = -delta;
        dy = delta;
        delta = *(s16*)(work + 4) - current->z;
        if (delta < 0)
            delta = -delta;
        dz = delta;
        if (dx < 20 && dy < 20 && dz < 20) {
            actor = *(void**)(work + 0x1C);
            if (actor != 0) {
                owner = *(void**)(work + 0x14);
                iterator = fn_80201B9C();
                moved = 0;
                reacted = 0;
                radius = fn_80201890(*(void**)(work + 0x18)) ? (u16)fn_8011F6F8() + 100 : 500;
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
                        const volatile u32* fallback = lbl_8023A760;
                        *(u32*)&fallback_point.x = fallback[0];
                        *(u32*)&fallback_point.y = fallback[1];
                        *(u32*)&fallback_point.z = fallback[2];
                        selected = &fallback_point;
                    }
                    point = *selected;
                    /* At 0x80150CC4 retail passes r22 directly even after the
                     * NULL fallback; fn_8011EB1C owns the NULL-sentinel case. */
                    candidate_type = fn_80201EB8(iterator);
                    candidate_rank = fn_80201B4C(iterator);
                    if (candidate_type == lbl_8064D18C &&
                        ((u32)candidate_rank <= 1 || candidate_rank == 2) &&
                        fn_80179004(&origin, &point) < radius &&
                        fn_8011EB1C(candidate) != 4) {
                        moved = 1;
                        if ((u32)fn_8020123C(0x3B, 0, fn_80201B54(iterator), 0) == 1) {
                            reaction = fn_801A717C();
                            if (reaction != 0) {
                                actor = fn_80201B54(iterator);
                                fn_801A74A0(reaction, 0);
                                fn_801A74A8(reaction, actor);
                                fn_801A7538(reaction, 1);
                                fn_801A7518(reaction, 5);
                                fn_801A7588(reaction, 2);
                                fn_801A764C(reaction, &origin);
                                fn_801A74D8(reaction, 0x1800);
                                fn_801A7668(reaction, owner);
                                fn_801A7670(reaction, 2);
                                fn_8020123C(11, 0, actor, reaction);
                                fn_801A7228(reaction);
                                reacted = 1;
                            }
                        }
                    }
                    iterator = fn_80201BC0(iterator);
                }
                if (reacted) {
                    u32 packed;
                    s16 kind;
                    fn_801D38BC(owner, &packed, &kind);
                    fn_80152404(&origin, kind, radius, 4, &packed);
                }
                if (moved) {
                    TargetVec3f* saved;
                    fn_8006D548(2, 0x40, 2, &origin, 0, 0, 0);
                    *(s16*)(work + 0) = origin.x;
                    *(s16*)(work + 2) = origin.y;
                    *(s16*)(work + 4) = origin.z;
                    *(u16*)(work + 12) = *(u16*)(work + 14);
                    actor = fn_80201814(*(void**)(work + 0x18));
                    if (actor != 0) {
                        saved = (TargetVec3f*)(*(u8**)((u8*)fn_80201B8C(actor) + 0x8C) + 0xA0);
                        *saved = origin;
                    }
                }
                if (!moved) {
                    **(s32**)(work + 0x1C) = 1;
                    fn_80149E28(instance);
                    completed = 1;
                }
            }
        } else if (*(u16*)(work + 12) > 1 &&
                   dx < 500 && dy < 500 && dz < 500) {
            --*(u16*)(work + 12);
        }
    }

    if (!completed && *(void**)(work + 0x1C) == 0 &&
        *(u16*)(instance + 0x132C) >= *(u16*)(instance + 0x132E))
        fn_80149E28(instance);
}
