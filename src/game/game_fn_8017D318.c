typedef signed short s16;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

#define MIN(a, b) ((b) < (a) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(value, low, high) MIN(MAX((value), (low)), (high))

void fn_8017D318(Vec3s* position, Vec3s* target, s16 z_offset,
                 Vec3s* velocity, s16 acceleration, s16 speed)
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

    velocity->x = CLAMP(velocity->x, -speed, speed);
    velocity->y = CLAMP(velocity->y, -speed, speed);
    velocity->z = CLAMP(velocity->z, -speed, speed);

    position->x += velocity->x;
    position->y += velocity->y;
    position->z += velocity->z;
}
