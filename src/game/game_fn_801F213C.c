typedef struct Vec3 {
    float x, y, z;
} Vec3;

float fn_801F213C(Vec3* a, Vec3* b)
{
    float dx;
    float dy;
    float dz;
    dx = a->x - b->x;
    dy = a->y - b->y;
    dz = a->z - b->z;
    return dx * dx + dy * dy + dz * dz;
}
