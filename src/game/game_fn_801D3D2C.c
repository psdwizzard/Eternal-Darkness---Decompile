typedef signed short s16;
typedef unsigned int u32;

extern void fn_80038308(void* object, int index, s16* value);

u32 fn_801D3D2C(void* object, s16 x, s16 y, s16 z)
{
    s16 limit_x;
    s16 limit_y;
    s16 limit_z;
    int result = 0;

    fn_80038308(object, 0, &limit_x);
    fn_80038308(object, 1, &limit_y);
    fn_80038308(object, 2, &limit_z);

    if (x < 0 && (x < 0 ? -x : x) >= limit_x) {
        result |= 1;
    }
    if (y < 0 && (y < 0 ? -y : y) > limit_y) {
        result |= 2;
    }
    if (z < 0 && (z < 0 ? -z : z) > limit_z) {
        result |= 4;
    }
    return result;
}
