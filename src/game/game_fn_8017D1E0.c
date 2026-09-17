typedef signed short s16;
typedef unsigned short u16;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

int fn_8017D1E0(Vec3s* first, Vec3s* second, u16 distance, u16 close,
                u16 limit, s16* counter)
{
    int result = 0;
    u16 dx;
    u16 dy;
    u16 dz;

    if (distance < close) {
        distance = close;
    }
    {
        int delta = second->x - first->x;
        if (delta >= 0) goto x_positive;
        delta = -delta;
x_positive:
        dx = delta;
    }
    if (dx < distance) {
        {
            int delta = second->y - first->y;
            if (delta >= 0) goto y_positive;
            delta = -delta;
y_positive:
            dy = delta;
        }
        if (dy < distance) {
            {
                int delta = second->z - first->z;
                if (delta >= 0) goto z_positive;
                delta = -delta;
z_positive:
                dz = delta;
            }
            if (dz < distance) {
                if (dx <= close && dy <= close && dz <= close) {
                    result = 1;
                } else if (counter != 0) {
                    int next = *counter + 1;
                    int value = limit;
                    if (next < value) {
                        value = next;
                    }
                    *counter = value;
                }
            }
        }
    }
    return result;
}
