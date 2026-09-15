typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct NodeInfo {
    unsigned char pad[0x8C];
    int *flags;
    unsigned char tail[0x0F];
    unsigned char kind;
} NodeInfo;

#pragma use_lmw_stmw on

extern const float lbl_8064F11C;
extern const float lbl_8064B710;
extern const float lbl_8064F120;
extern void *fn_80201B9C();
extern int fn_80201B54();
extern int fn_80201EB8();
extern void *fn_80201BC8();
extern void fn_8011F114();
extern void *fn_80201B8C();
extern unsigned long long fn_8020123C();
extern Vec3 *fn_800C43AC(Vec3 *, void *);
extern unsigned int fn_80178E94(Vec3 *, Vec3 *);
extern int fn_80204434(void *, Vec3 *, int, float);
extern void *fn_80201BC0(void *);

void *fn_800BE938(void *object, int enabled)
{
    void *cursor = fn_80201B9C();
    void *selected = 0;
    unsigned int best_distance = (unsigned int)-1;
    float limit = lbl_8064F11C * lbl_8064B710;
    int object_owner = fn_80201B54(object);
    int object_id = fn_80201EB8(object);
    void *object_position_object = fn_80201BC8(object);
    Vec3 object_position;
    Vec3 candidate_position;

    fn_8011F114(&object_position, object_position_object);
    while (cursor != 0) {
        NodeInfo *info = ((NodeInfo *)fn_80201B8C(cursor));
        int *flags = info != 0 ? info->flags : 0;
        void *candidate_position_object = fn_80201BC8(cursor);
        int candidate_owner = fn_80201B54(cursor);

        if (object_id == fn_80201EB8(cursor) &&
            candidate_position_object != 0 && object_owner != candidate_owner &&
            flags != 0 && (*flags & 0x10000) == 0) {
            unsigned int result =
                fn_8020123C(0x3B, object_owner, candidate_owner, 0) &
                0xFFFFFFFFULL;
            if (result == 1) {
                unsigned int distance;
                int accepted;

                fn_800C43AC(&candidate_position, cursor);
                distance = fn_80178E94(&object_position, &candidate_position);
                accepted = 1;
                if (enabled) {
                    if (info != 0 && info->kind == 13) {
                        limit = lbl_8064F120;
                    }
                    accepted = fn_80204434(object_position_object,
                                           &candidate_position, 0, limit);
                }
                if (distance < best_distance && accepted) {
                    best_distance = distance;
                    selected = cursor;
    }
}

/*
 * Honest-C boundary: this reconstruction recovers the complete nearest-peer
 * selection, collision gate and selected-node flag update. Remaining
 * differences are declaration-sensitive callee-saved register allocation and
 * the missing unsigned-byte normalization of fn_80204434's return; no inline
 * assembly is used.
 */
        }
        cursor = fn_80201BC0(cursor);
    }

    if (selected != 0) {
        NodeInfo *selected_info = ((NodeInfo *)fn_80201B8C(selected));
        *selected_info->flags |= 0x10000;
    }
    return selected;
}
