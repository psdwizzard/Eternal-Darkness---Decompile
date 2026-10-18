typedef struct Vec3 { float x, y, z; } Vec3;
#pragma use_lmw_stmw on
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Shape { unsigned char bytes[0x38]; } Shape;
typedef struct Collection {
    unsigned char pad00[0xC];
    void* context;
    unsigned char pad10[0x34];
    unsigned short count;
    unsigned char pad46[2];
    Shape* shapes;
} Collection;

extern float lbl_806503D8;
extern int fn_8013E284(const void*, const Shape*, const void*, Result*);
extern float PSVECSquareDistance(const Vec3*, const void*);
extern void fn_80140AEC(Shape*, Collection*);

Shape* fn_8013F898(Collection* collection, const void* value, Result* out)
{
    Result candidate;
    float best = lbl_806503D8;
    Shape* shape;
    Vec3* candidate_point;
    int count;
    void* context;
    int i;
    Shape* result;

    context = collection->context;
    shape = collection->shapes;
    count = collection->count;
    candidate_point = &candidate.point;
    result = 0;
    i = 0;

    for (; i < count; shape++, i++) {
        if (fn_8013E284(value, shape, context, &candidate)) {
            float distance = PSVECSquareDistance(candidate_point, value);
            if (distance < best) {
                best = distance;
                result = shape;
                *out = candidate;
                fn_80140AEC(shape, collection);
            }
        }
    }
    return result;
}
