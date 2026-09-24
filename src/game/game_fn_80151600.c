#include "src/game/game_targeting_types.h"

extern void fn_800BC100(s32, s32, u32*, s32, s32, s32, s32);
extern u32 fn_80152360(void*, u32);
extern s32 fn_802045AC(void*, TargetVec3f*);

/* Keep absolute differences branch-based, as in fn_8017E2B0. */
void fn_80151600(void* raw_instance)
{
    void* initial_actor;
    TargetVec3s* steering_actor;
    void* owner;
    u32 reaction_owner;
    u32 result_owner;
    TargetVec3s* current;
    void* iterator;
    void* reaction;
    s32 moved;
    s32 reacted;
    u32 iterated;
    void* candidate;
    void* initial_nearby;
    void* nearby;
    void* state;
    TargetVec3f effect_point;
    TargetVec3f origin;
    TargetVec3f selected_point;
    TargetVec3f located;
    TargetVec3f candidate_point;
    TargetVec3f fallback_point;
    u16 distance[3];
    u16* distance_cursor;
    u32 radius;
    u32 flags;
    s32 delta;
    s32 candidate_type;
    u32 candidate_rank;
    u32 packed;
    u32 entry;
    u32 copied;
    s16 kind;
    s32 handled;
    u8* instance;
    u8* work;
    instance = raw_instance;
    work = instance + 8;
    handled = 0;
    if ((((*((u16*)(instance + 0x132C))) & 3) == 0) &&
        ((*((void**)(work + 0x20))) != 0)) {
        current = fn_8017FDA8(*((void**)(work + 0x20)), 0);
        flags = fn_8019BBB4(*((void**)(work + 0x20)));
        initial_nearby = fn_80201814(*((void**)(work + 0x18)));
        if ((initial_nearby != 0) && (fn_80201BC8(initial_nearby) != 0)) {
            initial_actor = fn_801809A0(*((void**)(work + 0x20)));
            state = fn_80201B8C(initial_nearby);
            *((void**)((*((u8**)(((u8*)state) + 0x54))) + 0xF4)) =
                initial_actor;
        }
        if (((*((u16*)(instance + 0x132C))) & 15) == 0) {
            effect_point.x = current->x;
            effect_point.y = current->y;
            effect_point.z = current->z;
            fn_801AC9F4(0x2B4, 100, &effect_point, 2);
        }
        if (((flags & 5) != 0) && ((flags & 2) == 0)) {
            if (flags & 1) {
                steering_actor = fn_8019BB9C(*((void**)(work + 0x20)));
                fn_8017D908(current, steering_actor, (TargetVec3s*)(work + 6),
                            (s16) * (u16*)(work + 12), 1, 10);
                distance_cursor = distance;
                delta = ((TargetVec3s*)steering_actor)->x - current->x;
                if (delta >= 0)
                    goto actor_x_nonnegative;
                delta = -delta;
            actor_x_nonnegative:
                *distance_cursor++ = delta;
                delta = ((TargetVec3s*)steering_actor)->y - current->y;
                if (delta >= 0)
                    goto actor_y_nonnegative;
                delta = -delta;
            actor_y_nonnegative:
                *distance_cursor++ = delta;
                delta = ((TargetVec3s*)steering_actor)->z - current->z;
                if (delta >= 0)
                    goto actor_z_nonnegative;
                delta = -delta;
            actor_z_nonnegative:
                *distance_cursor = delta;
                if ((distance[0] < 50) && (distance[1] < 50)) {
                    fn_8019BBCC(*((void**)(work + 0x20)), 16, 0);
                    *((u16*)(work + 12)) = *((u16*)(work + 14));
                } else if ((((*((u16*)(work + 12))) > 1) &&
                            (distance[0] < 500)) &&
                           (distance[1] < 500) && (distance[2] < 500)) {
                    --(*((u16*)(work + 12)));
                }
            } else {
                fn_8017D908(current, (TargetVec3s*)work,
                            (TargetVec3s*)(work + 6),
                            (s16) * ((u16*)(work + 12)), 1, 2);
                distance_cursor = distance;
                delta = *((s16*)(work + 0)) - current->x;
                if (delta >= 0)
                    goto work_x_nonnegative;
                delta = -delta;
            work_x_nonnegative:
                *distance_cursor++ = delta;
                delta = *((s16*)(work + 2)) - current->y;
                if (delta >= 0)
                    goto work_y_nonnegative;
                delta = -delta;
            work_y_nonnegative:
                *distance_cursor++ = delta;
                delta = *((s16*)(work + 4)) - current->z;
                if (delta >= 0)
                    goto work_z_nonnegative;
                delta = -delta;
            work_z_nonnegative:
                *distance_cursor = delta;
                if ((distance[0] < 50) && (distance[1] < 50) &&
                    (distance[2] < 2)) {
                    fn_8019BBCC(*((void**)(work + 0x20)), 2, 0);
                    *((u16*)(work + 12)) = *((u16*)(work + 14));
                } else if ((((*((u16*)(work + 12))) > 1) &&
                            (distance[0] < 500)) &&
                           (distance[1] < 500) && (distance[2] < 500)) {
                    --(*((u16*)(work + 12)));
                }
            }
        }
        if ((fn_8019BBB4(*((void**)(work + 0x20))) & 2) != 0) {
            if ((*((void**)(work + 0x1C))) != 0) {
                owner = *((void**)(work + 0x14));
                iterator = fn_80201B9C();
                moved = 0;
                reacted = 0;
                radius = (fn_80201890(*((s32*)(work + 0x18))) != 0)
                             ? (((s32)fn_8011F6F8()) + 100)
                             : 500;
                result_owner = (u32)owner;
                reaction_owner = (u32)owner;
                origin.x = *((s16*)(work + 0));
                origin.y = *((s16*)(work + 2));
                origin.z = *((s16*)(work + 4));
                while (iterator != 0) {
                    TargetVec3f* chosen;
                    candidate = fn_80201BC8(iterator);
                    if (candidate != 0) {
                        fn_8011F114(&candidate_point, candidate);
                        chosen = &candidate_point;
                    } else {
                        fallback_point = *((const TargetVec3f*)lbl_8023A778);
                        chosen = &fallback_point;
                    }
                    selected_point = *chosen;
                    candidate_type =
                        fn_80201EB8(iterator, (int)(*((s32*)chosen)));
                    candidate_rank = (u32)fn_80201B4C(iterator);
                    if ((((lbl_8064D18C == candidate_type) &&
                          ((candidate_rank <= 1) ||
                           ((s32)candidate_rank == 2))) &&
                         (fn_80179004(&origin, &selected_point) < radius)) &&
                        (fn_8011EB1C(candidate) != 4)) {
                        moved = 1;
                        if ((u32)(fn_8020123C(0x3B, 0,
                                              (u32)fn_80201B54(iterator), 0) &
                                  0xFFFFFFFFULL) == 1) {
                            reaction = fn_801A717C();
                            if (reaction != 0) {
                                iterated = (u32)fn_80201B54(iterator);
                                fn_801A74A0(reaction, 0);
                                fn_801A74A8(reaction, iterated);
                                fn_801A7538(reaction, 1);
                                fn_801A7518(reaction, 5);
                                fn_801A7588(reaction, 2);
                                fn_801A764C(reaction, &origin);
                                fn_801A74D8(reaction, 0x1800);
                                fn_801A7668(reaction, reaction_owner);
                                fn_801A7670(reaction, 2);
                                fn_8020123C(11, 0, iterated, reaction);
                                fn_801A7228(reaction);
                                reacted = 1;
                            }
                        }
                    }
                    iterator = fn_80201BC0(iterator);
                }

                if (reacted) {
                    fn_801D38BC((s32)result_owner, &packed, &kind);
                    copied = packed;
                    fn_80152404(&origin, kind, radius, 4, &copied);
                }
                if (moved) {
                    entry = 0;
                    fn_800BC100(0, 0, &entry, 8, 0, 0, 0);
                    entry = fn_80152360((void*)lbl_8064D18C, entry);
                    fn_8019BBCC(*((void**)(work + 0x20)), 8, 0);
                    if ((u32)(fn_8020123C(0x9D, 0, *((void**)(work + 0x18)),
                                          entry) &
                              0xFFFFFFFFULL) == 1) {
                        nearby = fn_80201814(*((void**)(work + 0x18)));
                        *((u16*)(work + 0xC)) = *((u16*)(work + 0xE));
                        fn_8019BBCC(*((void**)(work + 0x20)), 0, 15);
                        if (nearby != 0) {
                            void* records;
                            state = fn_80201B8C(nearby);
                            records = *((void**)(((u8*)state) + 0x8C));
                            fn_802045AC(nearby, &located);
                            *((s16*)(work + 0)) = (s16)located.x;
                            *((s16*)(work + 2)) = (s16)located.y;
                            *((s16*)(work + 4)) =
                                (s16)(located.z + (*((u16*)(work + 0x12))));
                            *((TargetVec3f*)(((u8*)records) + 0xA0)) = located;
                        }
                    }
                } else {
                    *(*((s32**)(work + 0x1C))) = 1;
                    fn_80149E28(instance);
                    handled = 1;
                }
            }
        }
    }
    if (((!handled) && ((*((void**)(work + 0x1C))) == 0)) &&
        ((*((u16*)(instance + 0x132C))) >= (*((u16*)(instance + 0x132E))))) {
        fn_80149E28(instance);
    }
}
