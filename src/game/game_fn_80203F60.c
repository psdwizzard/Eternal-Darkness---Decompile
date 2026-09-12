#pragma use_lmw_stmw on

typedef unsigned char u8;
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;
typedef struct Result { unsigned int word[6]; } Result;

extern const float lbl_806515A8;
extern void fn_8013F3C0(Shape*, Vec3*, Vec3*, float);
extern int fn_80137350(void*, Shape*, void*, Result*, int, int*);
extern int fn_8013AD48(void*, Shape*, Result*);

u8 fn_80203F60(void* object, void* value, Vec3* position, Vec3* target, int resolve, float radius)
{
    Shape shape;
    Result result;
    int flag;
    int resolved = 0;

    position->z += lbl_806515A8;
    target->z = position->z;
    fn_8013F3C0(&shape, position, target, radius);
    if (fn_80137350(object, &shape, value, &result, 3, &flag) == 0 && resolve != 0)
        resolved = fn_8013AD48(object, &shape, &result);
    position->z -= lbl_806515A8;
    target->z = position->z;
    return resolved != 0;
}
