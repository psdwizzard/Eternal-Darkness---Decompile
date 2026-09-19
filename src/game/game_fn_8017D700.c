typedef signed short s16;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

#define MIN(a, b) ((b) < (a) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(value, low, high) MIN(MAX((value), (low)), (high))

void fn_8017D700(Vec3s* position, Vec3s* target, s16 z_offset,
                 Vec3s* velocity, s16 xy_acceleration, s16 xy_speed,
                 s16 z_acceleration, s16 z_speed)
{
    /* Keep the short deltas together for the original register allocation. */
    Vec3s delta;

    delta.y = target->y - position->y;
    delta.z = target->z - position->z - z_offset;
    delta.x = target->x - position->x;

    delta.x = CLAMP(delta.x, -xy_acceleration, xy_acceleration);
    delta.y = CLAMP(delta.y, -xy_acceleration, xy_acceleration);
    delta.z = CLAMP(delta.z, -z_acceleration, z_acceleration);

    velocity->x += delta.x;
    velocity->y += delta.y;
    velocity->z += delta.z;

    velocity->x = CLAMP(velocity->x, -xy_speed, xy_speed);
    velocity->y = CLAMP(velocity->y, -xy_speed, xy_speed);
    velocity->z = CLAMP(velocity->z, -z_speed, z_speed);

    position->x += velocity->x;
    position->y += velocity->y;
    position->z += velocity->z;
}
