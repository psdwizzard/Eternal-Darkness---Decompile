#pragma use_lmw_stmw on
typedef signed short s16;
typedef unsigned int u32;

extern s16 fn_80144A2C(u32, s16, s16, int);

u32 fn_8014549C(int index, float scale)
{
    int result = 0;
    s16 x = fn_80144A2C(0x30000, 0, 0x7FFF, index);
    s16 y = fn_80144A2C(0xC0000, 0, 0x7FFF, index);
    s16 z = fn_80144A2C(0x300000, 0, 0x7FFF, index);
    s16 w = fn_80144A2C(0xC00000, 0, 0x7FFF, index);
    float limit = (float)x * scale;
    if (limit < 0.0f)
        limit = -limit;
    if ((float)(y < 0 ? -y : y) <= limit) {
        if (x > 0)
            result |= 0x20000;
        else if (x < 0)
            result |= 0x10000;
    } else {
        limit = (float)y * scale;
        if (limit < 0.0f)
            limit = -limit;
        if ((float)(x < 0 ? -x : x) <= limit) {
            if (y > 0)
                result |= 0x80000;
            else if (y < 0)
                result |= 0x40000;
        }
    }
    limit = (float)z * scale;
    if (limit < 0.0f)
        limit = -limit;
    if ((float)(w < 0 ? -w : w) <= limit) {
        if (z > 0)
            result |= 0x200000;
        else if (z < 0)
            result |= 0x100000;
    } else {
        limit = (float)w * scale;
        if (limit < 0.0f)
            limit = -limit;
        if ((float)(z < 0 ? -z : z) <= limit) {
            if (w > 0)
                result |= 0x800000;
            else if (w < 0)
                result |= 0x400000;
        }
    }
    return result;
}
