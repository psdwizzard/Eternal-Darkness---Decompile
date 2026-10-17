typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct State {
    u8 pad00[0x2C];
    Vec3 source_position;
    Vec3 target_position;
    u8 pad44[0x10];
    s32 path_value;
    u8 pad58[0x1C];
    s32 target_id;
    s32 source_id;
    u8 pad7C[0x12];
    s16 timer;
} State;

typedef struct ObjectInfo {
    State* state;
    u8 pad04[0x9B];
    u8 subtype;
} ObjectInfo;

typedef struct GlobalMode {
    u8 pad00[8];
    s32 mode;
} GlobalMode;

extern GlobalMode lbl_803003C8;
extern s32 lbl_8064D18C;
extern float lbl_8064E228;
extern float lbl_8064E22C;
extern float lbl_8064E230;
extern float lbl_8064E234;
extern float lbl_8064E238;

extern void *fn_80201B9C(void);
extern void *fn_80201B8C(void*);
extern void *fn_80201BC8(void*);
extern void fn_8011F114(Vec3*, Vec3*);
extern u32 fn_801A7570(void*);
extern void* fn_80205288(void*);
extern int fn_80201B54(void*);
extern int fn_8011EB04(void *);
extern void* fn_80201C24(void*);
extern u32 fn_80157C80(void*);
extern int fn_80201EB8(void*);
extern int fn_80201B4C(void*);
extern int fn_80201B64(void*);
extern unsigned long long fn_8020123C(int, int, int, int);
extern u32 fn_80178E94(Vec3*, Vec3*);
extern s32 fn_80036A1C(void*, s32, s32*, Vec3*);
extern u8 fn_80204434(void*, Vec3*, float*, float);
extern u32 fn_800361F8(ObjectInfo*);
extern void* fn_80201BC0(void*);

static inline void GetTransformPosition(void* transform, Vec3* position)
{
    Vec3 temporary;
    Vec3* current;

    if (transform != 0) {
        fn_8011F114(&temporary, transform);
        current = &temporary;
    } else {
        current = position;
    }
    *position = *current;
}

void* fn_800365C8(void* source, void* query)
{
    void* candidate = fn_80201B9C();
    Vec3 source_position = {0.0f, 0.0f, 0.0f};
    void* selected;
    State* state;
    void* source_transform;
    void* linked;
    ObjectInfo* linked_info;
    s32 source_id;
    s32 previous_id;
    long query_value;
    s32 message_id;
    s32 subtype;
    s32 path_ok;
    u32 distance;
    float best_distance;
    s32 path_value;
    u32 message_result;

    best_distance = lbl_8064E228;
    selected = 0;
    state = ((ObjectInfo*)fn_80201B8C(source))->state;
    source_transform = fn_80201BC8(source);
    GetTransformPosition(source_transform, &source_position);
    message_id = fn_801A7570(query);
    linked = fn_80205288(source);
    if (linked != 0) {
        linked_info = fn_80201B8C(linked);
    } else {
        linked_info = 0;
    }
    subtype = linked_info != 0 ? linked_info->subtype : 19;
    source_id = fn_80201B54(source);

    {
        void* transform = linked != 0 ? fn_80201BC8(linked) : 0;
        previous_id = transform != 0 ? fn_8011EB04(transform) : -1;
    }
    if (linked == 0 || previous_id == 99 || previous_id == 198 || previous_id == 241) {
        return 0;
    }

    if (subtype == 18) {
        void* value = fn_80201C24(linked);
        if ((fn_80157C80(value) & 0x20) != 0 ||
            (fn_80157C80(value) & 0x80) != 0) {
            return 0;
        }
        best_distance = lbl_8064E22C;
    }

    query_value = message_id;
    while (candidate != 0 && selected == 0) {
        ObjectInfo* candidate_info = fn_80201B8C(candidate);
        Vec3 candidate_position = {0.0f, 0.0f, 0.0f};
        Vec3 path_position;
        s32 candidate_id = fn_80201B54(candidate);
        GetTransformPosition(fn_80201BC8(candidate), &candidate_position);

        if (fn_80201EB8(candidate) == lbl_8064D18C &&
            (fn_80201B4C(candidate) == 0 || fn_80201B4C(candidate) == 1) &&
            candidate != source &&
            (fn_80201B64(candidate) == 8 || fn_80201B64(candidate) == 9)) {
            message_id = fn_80201B54(candidate);
            message_result = fn_8020123C(0xC1, source_id, message_id, 0) & 0xFFFFFFFFULL;
            if (message_result != 0 &&
                (float)fn_80178E94(&candidate_position, &source_position) < lbl_8064E230) {
                path_ok = fn_80036A1C(candidate, query_value, &path_value, &path_position);
                distance = fn_80178E94(&path_position, &source_position);
                if (path_ok != 0 && (float)distance < best_distance &&
                    fn_80204434(source_transform, &path_position, 0, lbl_8064E234) != 0) {
                    state->source_id = message_id;
                    state->timer = 180;
                    selected = candidate;
                    state->source_position = source_position;
                } else if (path_ok != 0 && message_id == state->source_id) {
                    best_distance += lbl_8064E238;
                    if (path_ok != 0 && (float)distance < best_distance) {
                        selected = candidate;
                    }
                }

                if (selected != 0) {
                    if (lbl_803003C8.mode == 5 && candidate_info != 0 && (s32)fn_800361F8(candidate_info) == 0 &&
                        (message_result = fn_8020123C(0xC2, source_id, candidate_id, 0) &
                                          0xFFFFFFFFULL) != 0) {
                        selected = 0;
                    } else {
                        state->target_id = message_id;
                        state->target_position = path_position;
                        state->path_value = path_value;
                        break;
                    }
                }
            }
        }
        candidate = fn_80201BC0(candidate);
    }
    return selected;
}
