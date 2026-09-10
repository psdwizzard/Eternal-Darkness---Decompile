typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec3s { short x, y, z; } Vec3s;

int fn_8013D6A4(const Vec3* point, const Vec3s* minimum,
                const Vec3s* maximum)
{
    int result = point->x >= minimum->x && point->x <= maximum->x &&
                 point->y >= minimum->y && point->y <= maximum->y &&
                 point->z >= minimum->z && point->z <= maximum->z;
    return result;
}
