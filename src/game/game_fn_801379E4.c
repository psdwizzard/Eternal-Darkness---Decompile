typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;

typedef struct Result {
    Vec3 normal;
    Vec3 point;
} Result;

typedef struct Owner Owner;

extern void* fn_8015C2FC(int);
extern void* fn_8011F8FC(void*);
extern float fn_8011F6F8(void*);
extern void fn_8011F104(Vec3*, float, float, float);
extern void fn_80211A90(Vec3*, const Vec3*, float);
extern void fn_80211A48(const Vec3*, const Vec3*, Vec3*);
extern void fn_8013F3C0(Shape*, const Vec3*, const Vec3*, float);
extern void* fn_8013FBE4(Owner*, const void*, Result*, void*, unsigned int);
extern void* lbl_8064C4E4;

int fn_801379E4(Vec3* object, const Vec3* position, float distance)
{
    Shape shape;
    Result result;
    Vec3 end;
    Vec3 direction;
    Owner* owner;

    owner = fn_8015C2FC(2);
    direction = *(Vec3*)fn_8011F8FC(object);
    fn_80211A90(&direction, &direction, distance);
    fn_80211A48(position, &direction, &end);
    fn_8013F3C0(&shape, position, &end, fn_8011F6F8(lbl_8064C4E4));
    if (fn_8013FBE4(owner, &shape, &result, object, 0) != 0) {
        fn_8011F104(object, result.point.x, result.point.y, result.normal.z);
        return 1;
    }
    fn_8011F104(object, position->x, position->y, position->z);
    return 0;
}
