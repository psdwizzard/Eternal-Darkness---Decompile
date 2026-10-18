typedef unsigned short u16;

typedef struct Vec3 {
    float x;
    float y;
    float z;
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

typedef struct Contact {
    unsigned char bytes[24];
} Contact;

extern void* fn_8015C2FC(int);
extern void fn_8017DCE8(Vec3*, Vec3*, float);
extern void fn_8013F3C0(Shape*, Vec3*, Vec3*, float);
extern int fn_80142808(void*, Shape*, Contact*, float, float);
extern void PSVECAdd(Shape*, Vec3*, Vec3*);
extern void fn_8013F600(Contact*, Vec3*, float*);
extern int fn_8013F680(Vec3*);

u16 fn_8017E4E4(Vec3* position, Vec3* velocity, float acceleration,
                float radius, float threshold, float speed)
{
    Vec3 original = *position;
    Shape shape;
    Contact contact;
    Vec3 normal;
    float distance;
    void* collision = fn_8015C2FC(2);
    u16 result = 0;
    int kind;

    fn_8017DCE8(position, velocity, acceleration);
    fn_8013F3C0(&shape, &original, position, radius);
    kind = fn_80142808(collision, &shape, &contact, speed, threshold);
    switch (kind) {
    case 0:
    case 2:
        velocity->x = speed * (shape.axis.x * shape.length);
        velocity->y = speed * (shape.axis.y * shape.length);
        velocity->z = speed * (shape.axis.z * shape.length);
        PSVECAdd(&shape, velocity, position);
        break;
    case 3:
        result |= 1;
        velocity->x = speed * (shape.axis.x * shape.length);
        velocity->y = speed * (shape.axis.y * shape.length);
        velocity->z = speed * (shape.axis.z * shape.length);
        *position = shape.second;
        break;
    case 4:
        velocity->x = speed * (shape.axis.x * shape.length);
        velocity->y = speed * (shape.axis.y * shape.length);
        velocity->z = speed * (shape.axis.z * shape.length);
        *position = shape.second;
        fn_8013F600(&contact, &normal, &distance);
        if (fn_8013F680(&normal) == 2) {
            result |= 1;
        }
        break;
    }
    return result;
}
