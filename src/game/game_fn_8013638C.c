typedef unsigned char u8;
typedef unsigned short u16;

typedef float Matrix[3][4];

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct HitTriangle {
    Vec3 a, b, c;
} HitTriangle;

typedef struct ModelInfo {
    u8 pad0[0x1E];
    u16 lod;
    u8 pad20[0x6E];
    u16 scale_shift;
} ModelInfo;

extern ModelInfo* fn_8011F950(void* object);
extern Vec3* fn_8011F130(void* object);
extern void* fn_8011FE34(void* object);
extern u16 fn_8012B814(void* object);
extern u16 fn_8012B820(void* object, u16 index);
extern int fn_8012B830(void* object, u16 index);
extern int fn_80130998(int value, float scale);
extern void fn_8013133C(void* object, int limit);
extern int fn_801360B4(const Vec3* origin, const Vec3* direction, void* object,
                       u16 descriptor_index, HitTriangle* triangle,
                       float* distance, float max_distance);
extern void fn_802110A8(Matrix in, Matrix out);
extern void fn_802114E0(Matrix output, void* angles);
extern void fn_80211710(Matrix m, Vec3* in, Vec3* out);
extern void fn_80211A6C(const Vec3* a, const Vec3* b, Vec3* out);
extern void fn_80211A90(Vec3* in, Vec3* out, float scale);
extern float fn_80211B08(const Vec3* value);

extern float lbl_80650288;
extern float lbl_8065028C;

int fn_8013638C(Vec3* start, Vec3* end, void* object, HitTriangle* out_triangle,
                float* out_distance, float max_distance)
{
    Matrix matrix;
    HitTriangle triangle;
    Vec3 v0;
    Vec3 v1;
    Vec3 dir;
    float dist;
    ModelInfo* info;
    Vec3* origin;
    u16 count;
    float scale;
    float length;
    int mask;
    int limit;
    int id;
    u16 i;

    info = fn_8011F950(object);
    origin = fn_8011F130(object);
    count = fn_8012B814(object);
    mask = 0;
    scale = (int)(1 << info->scale_shift);

    fn_802114E0(matrix, fn_8011FE34(object));
    fn_802110A8(matrix, matrix);

    fn_80211A6C(start, origin, &v0);
    fn_80211710(matrix, &v0, &v0);
    fn_80211A90(&v0, &v0, scale);
    fn_80211A6C(end, origin, &v1);
    fn_80211710(matrix, &v1, &v1);
    fn_80211A90(&v1, &v1, scale);

    fn_80211A6C(&v1, &v0, &dir);
    length = fn_80211B08(&dir);
    if (lbl_80650288 == length) {
        return 0;
    }
    fn_80211A90(&dir, &dir, lbl_8065028C / length);

    if (max_distance > *(float*)((u8*)object + 0x2AC)) {
        max_distance = *(float*)((u8*)object + 0x2AC);
    }
    limit = fn_80130998(info->lod, max_distance);
    fn_8013133C(info, limit);

    for (i = 0; i < count; i++) {
        if (!(fn_8012B820(object, i) & 1)) {
            continue;
        }
        if (!(u8)fn_801360B4(&v0, &dir, object, i, &triangle, &dist, length)) {
            continue;
        }
        id = fn_8012B830(object, i);
        if (id == -1) {
            continue;
        }
        out_triangle->a = triangle.a;
        out_triangle->b = triangle.b;
        out_triangle->c = triangle.c;
        mask |= 1 << id;
        *out_distance = dist / scale;
    }
    return mask;
}
