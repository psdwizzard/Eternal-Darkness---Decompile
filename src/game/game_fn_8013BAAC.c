typedef float Mtx[3][4];
typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Quaternion { float x, y, z, w; } Quaternion;
typedef struct Shape {
    Vec3 first;
    Vec3 second;
    float radius;
    Vec3 axis;
    float length;
    Vec3 center;
    float bound_radius;
} Shape;
typedef struct Result { Vec3 normal; Vec3 point; } Result;
typedef struct Geometry {
    short position[3];
    unsigned char remainder[0x72];
} Geometry;
typedef struct Owner Owner;

extern void* fn_8011F9E4(void*, int);
extern void* fn_8011FA4C(void*, int);
extern int fn_8011F958(void*, void*);
extern void* fn_8011F130(void*);
extern void* fn_8011FE34(void*);
extern void* fn_8015C2FC(int);
extern void fn_80179DB0(float*, short*);
extern void fn_802114E0(Mtx, const Quaternion*);
extern void fn_80211710(const Mtx, const Vec3*, Vec3*);
extern void fn_80211A48(const Vec3*, const Vec3*, Vec3*);
extern void fn_8013F3C0(Shape*, const Vec3*, const Vec3*, float);
extern void* fn_8013FBE4(Owner*, const void*, Result*, void*, unsigned int);
extern Vec3 lbl_8063D378;

int fn_8013BAAC(void* target, void* object, float radius)
{
    Mtx rotation;
    Shape shape;
    Result result;
    Vec3 start;
    Vec3 end;
    Geometry* first;
    Geometry* second;
    int index;

    first = fn_8011F9E4(object, 0);
    second = fn_8011FA4C(object, 0);
    index = fn_8011F958(object, target);
    if (index != -1) {
        Vec3* translation;
        Quaternion* angles;
        Owner* owner;

        translation = fn_8011F130(object);
        angles = fn_8011FE34(object);
        owner = fn_8015C2FC(2);
        fn_80179DB0(&start.x, first[index].position);
        fn_80179DB0(&end.x, second[index].position);
        fn_802114E0(rotation, angles);
        fn_80211710(rotation, &start, &start);
        fn_80211710(rotation, &end, &end);
        fn_80211A48(translation, &start, &start);
        fn_80211A48(translation, &end, &end);
        fn_8013F3C0(&shape, &end, &start, radius);
        if (fn_8013FBE4(owner, &shape, &result, object, 0) != 0)
            return 1;
        fn_8013F3C0(&shape, &lbl_8063D378, &start, radius);
        return fn_8013FBE4(owner, &shape, &result, object, 0) != 0;
    }
    return 1;
}
