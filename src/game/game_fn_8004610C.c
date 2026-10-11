typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned char u8;

typedef struct ActionState {
    u8 pad_00[0x38];
    s32 action;
} ActionState;

typedef struct Owner {
    u8 pad_00[0xC4];
    ActionState *state;
} Owner;

typedef struct TargetLink {
    u8 pad_00[0x44];
    s32 object_id;
} TargetLink;

typedef struct ObjectData {
    u8 pad_00[0x38];
    Owner *owner;
    u8 pad_3C[0x50];
    TargetLink *target;
} ObjectData;

extern s32 fn_80201B44(void);
extern void *fn_80201814(s32 id);
extern ObjectData *fn_80201B8C(void *object);
extern s32 fn_8006BCB4(Owner *owner);
extern s32 fn_800462C8(s32 check_state);
extern s32 fn_8006B804(void *owner, s32 event);
extern s32 fn_8006B70C(u8 *owner, s32 value);
extern s32 fn_80070CD8(s32 flags);
extern u64 fn_8020123C(s32 kind, s32 sender, s32 recipient, s32 data);
extern s32 fn_8006EDA0(Owner *owner, void *source);

s32 fn_8004610C(s32 event)
{
    s32 action;
    void *object;
    s32 target_id;
    void *target_object;
    ObjectData *data;
    s32 failed;

    action = -1;

    object = fn_80201814(fn_80201B44());
    if (object != 0) {
        target_id = fn_80201B8C(object)->target->object_id;
        if (target_id != 0) {
            target_object = fn_80201814(target_id);
            if (target_object != 0) {
                data = fn_80201B8C(target_object);
                action = fn_8006BCB4(data->owner);
                if (fn_800462C8(0) == 0) {
                    if (fn_8006B804(data->owner, event) != 0) {
                        fn_8020123C(0x52, 0, target_id, 0);
                        data->owner->state->action = 12;
                        if ((u32)(fn_8020123C(0x53, 0, target_id,
                                (s32)&data->owner->state->action) & 0xFFFFFFFFULL) == 1) {
                            action = 12;
                        }
                    } else if (fn_8006B70C((u8 *)data->owner, event) != 0 &&
                               fn_80070CD8(0) != 0) {
                        fn_8020123C(0x52, 0, target_id, 0);
                        data->owner->state->action = 22;
                        if ((u32)(fn_8020123C(0x53, 0, target_id,
                                (s32)&data->owner->state->action) & 0xFFFFFFFFULL) == 1) {
                            action = 22;
                        }
                    }
                }
                if (action > 0) {
                    failed = 0;
                    if (fn_8006EDA0((Owner *)object, target_object) == 0) {
                        failed = 1;
                    }
                    if (action != 12 && failed != 0) {
                        fn_8020123C(0x52, 0, target_id, 0);
                        action = -1;
                    }
                }
            }
        }
    }
    return action;
}
