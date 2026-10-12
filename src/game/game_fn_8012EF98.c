typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

typedef struct TranslationDistance {
    Vec3 translation;
    float distance;
} TranslationDistance;

typedef struct QueryResult {
    u8 pad_0[8];
    Vec3 position;
    Vec3 direction;
    u8 pad_20[8];
} QueryResult;

typedef struct QueryVectors {
    Vec3 position;
    Vec3 direction;
} QueryVectors;

typedef struct EntryRecord {
    u8 pad_0[0xE];
    u16 transform_index;
} EntryRecord;

typedef struct Entry {
    u8 pad_0[4];
    EntryRecord* record;
} Entry;


typedef struct ObjectLayout {
    u8 pad_0[0x240];
    Entry** entries;
    u8 pad_244[0x10];
    u32 flags;
} ObjectLayout;

typedef float MatrixArray[3][4];
typedef struct Matrix34 {
    float m[3][4];
} Matrix34;

extern Vec3 lbl_805AADC8[10];
extern int lbl_8064CF30;
extern int lbl_8064CF34;

extern void fn_80125ECC(void*);
extern void fn_80127FD8(void*, int, MatrixArray);
extern void fn_80211A6C(const Vec3*, const Vec3*, Vec3*);
extern float fn_80211B08(const Vec3*);
extern void fn_80211AAC(const Vec3*, Vec3*);
extern int fn_8013DE44(const Vec3*, const Vec3*, const Vec3*, float,
                       float*, u8);
extern void fn_80211A90(const Vec3*, Vec3*, float);
extern void fn_80211A48(const Vec3*, const Vec3*, Vec3*);
extern void fn_80211B64(const Vec3*, const Vec3*, Vec3*);
extern float fn_80211B44(const Vec3*, const Vec3*);
extern float fn_800490E8(float, float);
extern u32 fn_802110A8(void*, void*);
extern void fn_8017AD00(const Matrix34*, const Vec3*, Vec3*);
extern void fn_8017A244(const Vec3*, Vec4*, float);

int fn_8012EF98(void* object_ptr, int index, QueryResult* first,
                QueryResult* second, const Vec3* target, Vec4* output,
                float limit)
{
    ObjectLayout* object = (ObjectLayout*)object_ptr;
    MatrixArray matrix;
    Matrix34 inverse;
    QueryVectors hit;
    Vec3 target_delta;
    Vec3 cross;
    Vec3 local_axis;
    Vec3 axis;
    Vec3 local_point;
    Vec3 direction;
    TranslationDistance frame;
    Vec3 debug_direction;
    Vec3* debug_vectors = lbl_805AADC8;
    float intersection;
    float cross_length;
    float axis_dot;
    float angle;
    float axis_angle;
    int result = 0;
    Entry* entry;

    fn_80125ECC(object_ptr);
    entry = object->entries[index];
    if (entry != 0) {
        fn_80127FD8(object_ptr, entry->record->transform_index, matrix);
        frame.translation.x = matrix[0][3];
        frame.translation.y = matrix[1][3];
        frame.translation.z = matrix[2][3];

        fn_80211A6C(target, &frame.translation, &target_delta);
        frame.distance = fn_80211B08(&target_delta);
        fn_80211AAC(&target_delta, &target_delta);
        fn_80211AAC(&first->direction, &direction);

        if (fn_8013DE44(&first->position, &direction, &frame.translation, frame.distance,
                        &intersection, 0)) {
            result = 1;
            fn_80211A90(&direction, &direction, intersection);
            fn_80211A48(&first->position, &direction, &hit.position);
            fn_80211A6C(&hit.position, &frame.translation, &local_point);
            fn_80211B64(&local_point, &target_delta, &cross);
            cross_length = fn_80211B08(&cross);
            fn_80211AAC(&cross, &cross);
            {
                float local_dot = fn_80211B44(&local_point, &target_delta);
                angle = fn_800490E8(cross_length, local_dot);
            }

            if ((object->flags & 0x80000000U) != 0) {
                fn_80211B64(&first->direction, &target_delta, &axis);
                axis_dot = fn_80211B44(&first->direction, &target_delta);
            } else {
                fn_80211B64(&second->direction, &target_delta, &axis);
                axis_dot = fn_80211B44(&second->direction, &target_delta);
            }
            axis_angle = fn_800490E8(fn_80211B08(&axis), axis_dot);
            if (axis_angle > limit) {
                angle = limit + (angle - axis_angle);
            }

            fn_802110A8(matrix, &inverse);
            fn_8017AD00(&inverse, &cross, &local_axis);
            fn_8017A244(&local_axis, output, angle);

            if (lbl_8064CF30 != 0 && index == lbl_8064CF34) {
                debug_vectors[0] = *target;
                debug_vectors[3] = first->position;
                debug_direction = first->direction;
                fn_80211AAC(&debug_direction, &debug_direction);
                fn_80211A90(&debug_direction, &debug_direction, frame.distance);
                fn_80211A48(&debug_vectors[3], &debug_direction,
                             &debug_vectors[4]);

                debug_vectors[5] = second->position;
                debug_direction = second->direction;
                fn_80211AAC(&debug_direction, &debug_direction);
                fn_80211A90(&debug_direction, &debug_direction, frame.distance);
                fn_80211A48(&debug_vectors[5], &debug_direction,
                             &debug_vectors[6]);

                debug_vectors[7] = frame.translation;
                fn_80211A48(&debug_vectors[7], &local_point,
                             &debug_vectors[8]);
            }
        }
    }
    return result;
}
