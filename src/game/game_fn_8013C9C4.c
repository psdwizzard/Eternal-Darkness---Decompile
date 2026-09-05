typedef struct Vec3 { float x, y, z; } Vec3;
typedef struct Vec3s { short x, y, z; } Vec3s;

int fn_8013C9C4(const Vec3s* value, const Vec3* point, int axis)
{
    int first_value;
    int second_value;
    int first_point;
    int second_point;
    int result;

    switch (axis) {
    case 0:
        first_point = point->y;
        second_point = point->z;
        first_value = value->y;
        second_value = value->z;
        break;
    case 1:
        first_point = point->x;
        second_point = point->z;
        first_value = value->x;
        second_value = value->z;
        break;
    case 2:
        first_point = point->x;
        second_point = point->y;
        first_value = value->x;
        second_value = value->y;
        break;
    }

    if (first_value < first_point) {
        if (second_value < second_point) {
            result = 2;
        } else {
            result = 1;
        }
    } else {
        if (second_value < second_point) {
            result = 3;
        } else {
            result = 0;
        }
    }
    return result;
}
