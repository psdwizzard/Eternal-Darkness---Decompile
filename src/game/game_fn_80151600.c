/* NonMatching: independent behavior-complete reconstruction from retail control
 * flow. GC/1.3 emits a 0x70-byte frame and saves r22-r31, while retail uses a
 * 0xC0-byte frame and saves r21-r31; local lifetime and register-allocation
 * differences then persist through the iterator/reaction path. */
#include "src/game/game_targeting_types.h"

#define fn_80201B54(...) ((void *)fn_80201B54(__VA_ARGS__))

void fn_80151600(void* raw_instance)
{
    u8* instance = raw_instance;
    u8* work = instance + 8;
    TargetVec3s* current;
    void* actor;
    void* iterator;
    void* candidate;
    void* reaction;
    void* nearby;
    void* state;
    TargetVec3s* steering_target;
    TargetVec3f origin;
    TargetVec3f point;
    u16 dx, dy, dz;
    u16 radius;
    s32 flags;
    s32 delta;
    s32 candidate_type;
    s32 candidate_rank;
    s32 moved = 0;
    s32 reacted = 0;

    if ((*(u16*)(instance + 0x132C) & 3) == 0 && *(void**)(work + 0x20) != 0) {
        current = fn_8017FDA8(*(void**)(work + 0x20), 0);
        flags = fn_8019BBB4(*(void**)(work + 0x20));
        nearby = fn_80201814(*(void**)(work + 0x18));
        if (nearby != 0 && fn_80201BC8(nearby) != 0) {
            actor = fn_801809A0(*(void**)(work + 0x20));
            state = fn_80201B8C(nearby);
            *(void**)(*(u8**)((u8*)state + 0x54) + 0xF4) = actor;
        }

        if ((*(u16*)(instance + 0x132C) & 15) == 0) {
            point.x = current->x;
            point.y = current->y;
            point.z = current->z;
            fn_801AC9F4(0x2B4, 100, &point, 2);
        }

        if ((flags & 5) != 0 && (flags & 2) == 0) {
            if (flags & 1) {
                actor = fn_8019BB9C(*(void**)(work + 0x20));
                fn_8017D908(current, actor, work + 6,
                            *(s16*)(work + 12), 1, 10);
                steering_target = actor;
            } else {
                fn_8017D908(current, work, work + 6, *(s16*)(work + 12), 1,
                            2);
                steering_target = (TargetVec3s*)work;
            }
            delta = steering_target->x - current->x;
            if (delta < 0)
                delta = -delta;
            dx = delta;
            delta = steering_target->y - current->y;
            if (delta < 0)
                delta = -delta;
            dy = delta;
            delta = steering_target->z - current->z;
            if (delta < 0)
                delta = -delta;
            dz = delta;
            if (dx < 50 && dy < 50 && ((flags & 1) != 0 || dz < 2)) {
                fn_8019BBCC(*(void**)(work + 0x20), flags & 1 ? 16 : 2, 0);
                *(u16*)(work + 12) = *(u16*)(work + 14);
            } else if (*(u16*)(work + 12) > 1 && dx < 500 && dy < 500 && dz < 500) {
                --*(u16*)(work + 12);
            }
        }

        if ((fn_8019BBB4(*(void**)(work + 0x20)) & 2) != 0) {
            actor = *(void**)(work + 0x1C);
            if (actor != 0) {
                iterator = fn_80201B9C();
                radius = fn_80201890(*(void**)(work + 0x18)) ? (u16)(fn_8011F6F8() + 100.0f) : 500;
                origin.x = *(s16*)(work + 0);
                origin.y = *(s16*)(work + 2);
                origin.z = *(s16*)(work + 4);
                while (iterator != 0) {
                    candidate = fn_80201BC8(iterator);
                    if (candidate != 0)
                        fn_8011F114(&point, candidate);
                    else {
                        const volatile u32* fallback = lbl_8023A778;
                        point.x = *(const volatile float*)&fallback[0];
                        point.y = *(const volatile float*)&fallback[1];
                        point.z = *(const volatile float*)&fallback[2];
                    }
                    /* Retail 0x80151A44 likewise passes the possibly-NULL r22;
                     * preserve the callee's NULL-sentinel contract. */
                    candidate_type = fn_80201EB8(iterator);
                    candidate_rank = fn_80201B4C(iterator);
                    if (candidate_type == lbl_8064D18C &&
                        candidate_rank <= 2 &&
                        fn_80179004(&origin, &point) < radius &&
                        fn_8011EB1C(candidate) != 4) {
                        moved = 1;
                        fn_8020123C(0x3B, 0, fn_80201B54(iterator), 0);
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
                            fn_801A7668(reaction, *(void**)(work + 0x14));
                            fn_801A7670(reaction, 2);
                            fn_8020123C(11, 0, actor, reaction);
                            fn_801A7228(reaction);
                            reacted = 1;
                        }
                    }
                    iterator = fn_80201BC0(iterator);
                }
                if (reacted) {
                    u32 packed;
                    s16 kind;
                    fn_801D38BC(current, &packed, &kind);
                    fn_80152404(&origin, kind, radius, 4, &packed);
                }
                if (!moved) {
                    **(s32**)(work + 0x1C) = 1;
                    fn_80149E28(instance);
                    reacted = 1;
                }
            }
        }
    }

    if (!reacted && *(void**)(work + 0x1C) == 0 &&
        *(u16*)(instance + 0x132C) >= *(u16*)(instance + 0x132E))
        fn_80149E28(instance);
}
