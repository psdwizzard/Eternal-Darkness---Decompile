typedef signed short s16;
typedef unsigned char u8;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct Vec3u8 {
    u8 x;
    u8 y;
    u8 z;
} Vec3u8;

#define MIN(a, b) ((b) < (a) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(value, low, high) MIN(MAX((value), (low)), (high))

void fn_8017D508(Vec3s* position, Vec3s* target, s16 z_offset,
                 Vec3s* velocity, s16 acceleration, Vec3u8* speed)
{
    Vec3s delta;

    delta.y = target->y - position->y;
    delta.z = target->z - position->z - z_offset;
    delta.x = target->x - position->x;

    delta.x = CLAMP(delta.x, -acceleration, acceleration);
    delta.y = CLAMP(delta.y, -acceleration, acceleration);
    delta.z = CLAMP(delta.z, -acceleration, acceleration);

    velocity->x += delta.x;
    velocity->y += delta.y;
    velocity->z += delta.z;

    velocity->x = CLAMP(velocity->x, -speed->x, speed->x);
    velocity->y = CLAMP(velocity->y, -speed->y, speed->y);
    velocity->z = CLAMP(velocity->z, -speed->z, speed->z);

    position->x += velocity->x;
    position->y += velocity->y;
    position->z += velocity->z;
}
