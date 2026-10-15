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

typedef struct Result { Vec3 normal; Vec3 point; } Result;

typedef struct Owner {
    unsigned char pad00[0x20];
    unsigned char collection[0x80];
    unsigned char object[0x44];
    void *shapes;
} Owner;

extern void *fn_80201BC8(void *object);
extern void fn_8011F114(Vec3 *destination, Vec3 *source);
extern void *fn_8012AB2C(unsigned char *owner);
extern void fn_8013F3C0(Shape *out, const Vec3 *first,
                       const Vec3 *second, float radius);
extern void *fn_8013FBE4(Owner *owner, const void *value, Result *out,
                        void *context, unsigned int flags);

int fn_8003E0E4(void *object, Vec3 *destination, float radius,
                float height, int enabled)
{
    Shape shape;
    Result hit;
    Vec3 position;
    void *source;
    Owner *owner;
    int clear = 1;

    source = fn_80201BC8(object);

    fn_8011F114(&position, source);
    owner = fn_8012AB2C(source);
    if (enabled) {
        float displacement = radius + height;
        position.z += displacement;
        destination->z += displacement;
    }
    fn_8013F3C0(&shape, &position, destination, radius);
    if (fn_8013FBE4(owner, &shape, &hit, 0, 8) != 0)
        clear = 0;
    if (enabled)
        destination->z -= radius + height;
    return clear;
}
