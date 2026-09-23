typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

extern void fn_801989CC(u8, void*, s16*);
extern void* memcpy(void*, const void*, unsigned long);

static inline int absolute(u32 value)
{
    if ((int)value < 0) {
        return -value;
    }
    return value;
}

u8 fn_80198850(void* context, s16* points, u8 count, s16* center,
                 s16* offset)
{
    s16 extreme[3];
    u32 max_x = 0;
    u32 max_y = 0;
    u32 max_z = 0;
    s16* point;
    u32 dx;
    u32 dy;
    u32 dz;
    int i;

    fn_801989CC(count - 1, context, points);
    memcpy(extreme, points, 6);

    for (i = 0; i < count; i++) {
        point = &points[i * 3];
        dx = absolute(points[0] - point[0]);
        dy = absolute(points[1] - point[1]);
        dz = absolute(points[2] - point[2]);
        if (dx > max_x) {
            max_x = dx;
            extreme[0] = point[0];
        }
        if (dy > max_y) {
            max_y = dy;
            extreme[1] = point[1];
        }
        if (dz > max_z) {
            max_z = dz;
            extreme[2] = point[2];
        }
    }

    center[0] = points[0] + ((extreme[0] - points[0]) >> 1);
    center[1] = points[1] + ((extreme[1] - points[1]) >> 1);
    center[2] = points[2] + ((extreme[2] - points[2]) >> 1);
    offset[0] = points[0] - center[0];
    offset[1] = points[1] - center[1];
    offset[2] = points[2] - center[2];
    return count;
}
