#pragma use_lmw_stmw on

typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Owner {
    unsigned char pad00[0x20];
    unsigned char collection[0x80];
    unsigned char object[0x44];
    void* shapes;
} Owner;
typedef struct Hit { unsigned char pad00[4]; unsigned char index; } Hit;

extern float lbl_806503D8;
extern void* fn_8013F980(void*, const void*, Result*);
extern Hit* fn_8013E188(const void*, const void*, Result*);
extern void* fn_801439E0(const void*, Result*, void*, unsigned int);
extern float PSVECSquareDistance(const void*, const Vec3*);

void* fn_8013FBE4(Owner* owner, const void* value, Result* out,
                  void* context, unsigned int flags)
{
    Result second_result;
    Result first_result;
    Result extra_result;
    float best = lbl_806503D8;
    void* first;
    Hit* second;
    void* extra = 0;
    signed char selected = 0;

    first = fn_8013F980(owner->collection, value, &first_result);
    second = fn_8013E188(value, owner->object, &second_result);
    if (flags & 1)
        extra = fn_801439E0(value, &extra_result, context, flags);
    if (first != 0) {
        best = PSVECSquareDistance(value, (Vec3*)&first_result);
        selected = 1;
    }
    if (second != 0) {
        float distance = PSVECSquareDistance(value, (Vec3*)&second_result);
        if (distance < best) {
            best = distance;
            selected = 2;
        }
    }
    if (extra != 0 && PSVECSquareDistance(value, (Vec3*)&extra_result) < best)
        selected = 3;

    if (selected == 1) {
        *out = first_result;
        return first;
    }
    if (selected == 2) {
        *out = second_result;
        return (unsigned char*)owner->shapes + second->index * 0x38;
    }
    if (selected == 3) {
        *out = extra_result;
        return extra;
    }
    return 0;
}
