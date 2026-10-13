typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct PathNode {
    const short *position;
    struct PathNode *neighbors[8];
    struct PathNode *parent;
    float cost;
    float estimate;
    float total;
    unsigned char flags;
    unsigned char neighbor_count;
    unsigned char pad[2];
} PathNode;

typedef struct RuntimeState {
    unsigned char pad[0xAC];
    int pool_index;
    int slot_index;
} RuntimeState;

typedef struct ObjectData {
    unsigned char pad[0x8C];
    RuntimeState *runtime;
} ObjectData;

typedef struct Slot {
    int state;
    int object_id;
    int start_frame;
    int last_frame;
    int active;
    unsigned char flags;
    unsigned char pad15[3];
} Slot;

typedef struct Pool {
    PathNode *first_path[100];
    PathNode *second_path[100];
    unsigned char pad320[8];
    int environment;
    int object_id;
    int frame;
    unsigned char flags;
    unsigned char pad335[3];
} Pool;

typedef struct OSMessageQueue OSMessageQueue;
typedef struct Entry80201814 Entry80201814;
typedef struct Object80201C48 Object80201C48;

extern const Vec3 lbl_802397F0;
extern PathNode *lbl_80320C60[100];
extern Slot lbl_80320DF0[];
extern Pool lbl_80320FD0[];
extern OSMessageQueue lbl_805E2B1C;
extern OSMessageQueue lbl_805E2B7C;
extern int lbl_8064B700;
extern int lbl_8064B704;
extern int lbl_8064CA80;
extern const float lbl_8064F100;
extern const float lbl_8064F104;

extern void fn_801EF788(void);
extern int fn_8020D318(OSMessageQueue *queue, void **message, int flags);
extern int fn_8020D250(OSMessageQueue *queue, void *message, int flags);
extern int OSDisableInterrupts(void);
extern int OSRestoreInterrupts(int enabled);
extern Entry80201814 *fn_80201814(int id);
extern void *fn_80201BC8(void *object);
extern void *fn_80201B94(unsigned char *object);
extern void *fn_80201B8C(unsigned char *object);
extern void *fn_80201C48(Object80201C48 *data);
extern float fn_8011F6F8(void *transform);
extern void fn_8011F114(Vec3 *dest, Vec3 *source);
extern int fn_802045AC(void *object, Vec3 *position);
extern void fn_800BC74C(int reset);
extern PathNode *fn_800BC100(const short *key, Vec3 *origin, int *out_index,
                           unsigned int flags, int *min_dist, int *max_dist, Vec3 *other);
extern int fn_800BD3C8(PathNode *start, PathNode *goal);
extern void fn_800BCF08(Vec3 *position, PathNode **path, float radius);
extern void fn_800BD23C(void);
extern void *memcpy(void *dest, const void *source, unsigned long size);

/* Processes queued path requests and publishes their paths to the object pools. */
void fn_800BD94C(void)
{
    Vec3 origin;
    Vec3 goal;
    void *message;
    int has_goal;
    int path_found;
    int goal_id;
    int interrupts;
    int object_id;
    void *object;
    void *data;
    Vec3 *transform;
    float radius;
    void *goal_object;
    Vec3 *goal_transform;
    PathNode *start;
    PathNode *end;
    ObjectData *object_data;
    RuntimeState *runtime;

    lbl_8064CA80 = 0;
    /* These values persist when a later object lookup cannot update them. */
    has_goal = 0;
    path_found = 0;
    goal_id = 0;
    goal = lbl_802397F0;
    fn_801EF788();

    for (;;) {
        fn_8020D318(&lbl_805E2B1C, &message, 1);
        if ((int)message == -0x6B5) {
            lbl_8064CA80 = 0;
            while (fn_8020D318(&lbl_805E2B1C, &message, 0) != 0) {
            }
            fn_8020D250(&lbl_805E2B7C, 0, 1);
            continue;
        }
        if ((int)message == -0x1A0A) {
            if (lbl_8064CA80 == 0) {
                lbl_8064CA80 = 1;
            }
            continue;
        }
        if (lbl_8064CA80 == 0) {
            continue;
        }

        interrupts = OSDisableInterrupts();
        object_id = (int)message;
        object = fn_80201814(object_id);
        transform = object != 0 ? fn_80201BC8(object) : 0;
        radius = transform != 0 ? fn_8011F6F8(transform) : lbl_8064F100;
        data = object != 0 ? fn_80201B94(object) : 0;
        if (object != 0 && data != 0 && transform != 0) {
            fn_8011F114(&origin, transform);
            goal_id = (int)fn_80201C48(data);
        }
        if (goal_id == -1 && object != 0) {
            fn_802045AC(object, &goal);
            has_goal = 1;
        } else {
            goal_object = fn_80201814(goal_id);
            goal_transform = goal_object != 0 ? fn_80201BC8(goal_object) : 0;
            if (goal_object != 0 && goal_transform != 0) {
                fn_8011F114(&goal, goal_transform);
                has_goal = 1;
            }
        }
        OSRestoreInterrupts(interrupts);

        if (has_goal) {
            fn_800BC74C(0);
            origin.z += lbl_8064F104;
            goal.z += lbl_8064F104;
            if (lbl_8064B704 != 0) {
                start = fn_800BC100(0, &origin, 0, 0xC2, &lbl_8064B700, 0, &goal);
            } else {
                start = fn_800BC100(0, &origin, 0, 0x42, 0, 0, &goal);
            }
            end = fn_800BC100(0, &goal, 0, 0x42, 0, 0, 0);
            if (start != 0 && end != 0) {
                /* Searching backwards gives a parent chain from origin to goal. */
                path_found = fn_800BD3C8(end, start);
                fn_800BCF08(&origin, lbl_80320C60, radius);
            }

            interrupts = OSDisableInterrupts();
            object = fn_80201814(object_id);
            if (object != 0) {
                object_data = fn_80201B8C(object);
                if (object_data != 0) {
                    runtime = object_data->runtime;
                    if (runtime != 0) {
                        if (object_id != lbl_80320DF0[runtime->slot_index].object_id ||
                            object_id != lbl_80320FD0[runtime->pool_index].object_id) {
                            fn_800BD23C();
                            /* ASM: nop preserves the retail diagnostic call pad;
                             * a side-effect-free C statement is optimized away. */
                            asm { nop }
                        }
                        lbl_80320DF0[runtime->slot_index].active = 1;
                        switch (lbl_80320DF0[runtime->slot_index].state) {
                        case -2:
                        case -1:
                        case 1:
                            memcpy(lbl_80320FD0[runtime->pool_index].first_path,
                                   lbl_80320C60, 0x190);
                            break;
                        case 0:
                            memcpy(lbl_80320FD0[runtime->pool_index].second_path,
                                   lbl_80320C60, 0x190);
                            break;
                        }
                        if (path_found == 0) {
                            lbl_80320DF0[runtime->slot_index].flags |= 4;
                            lbl_80320FD0[runtime->pool_index].flags |= 4;
                        } else {
                            lbl_80320DF0[runtime->slot_index].flags &= ~4;
                            lbl_80320FD0[runtime->pool_index].flags &= ~4;
                        }
                    }
                }
            }
            OSRestoreInterrupts(interrupts);
        } else {
            interrupts = OSDisableInterrupts();
            object = fn_80201814(object_id);
            object_data = object != 0 ? fn_80201B8C(object) : 0;
            if (object_data != 0 && object_data->runtime != 0) {
                lbl_80320DF0[object_data->runtime->slot_index].state = -1;
                lbl_80320DF0[object_data->runtime->slot_index].flags &= ~2;
            }
            OSRestoreInterrupts(interrupts);
        }
    }
}
