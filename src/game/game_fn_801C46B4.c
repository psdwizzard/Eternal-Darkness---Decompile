typedef signed short s16;
typedef unsigned short u16;

int salCheckVolErrorAndResetDelta(u16* reset, u16* direction, u16* position, u16 target,
                u16* flags, u16 mask)
{
    s16 delta;
    s16 step;

    if (target != *position) {
        delta = (s16)target - (s16)*position;
        if (delta >= 0x20 && delta < 0xA0) {
            step = delta >> 5;
            if (step < 5)
                flags[step] |= mask;
            *direction = 1;
            *position += step << 5;
            return 1;
        }
        if (delta <= -0x20 && delta > -0xA0) {
            step = -delta >> 5;
            if (step < 5)
                flags[step] |= mask;
            *direction = 0xFFFF;
            *position -= step << 5;
            return 1;
        }
        if (target == 0 && delta > -0x20) {
            *position = 0;
            *reset = 0;
        }
    }
    *direction = 0;
    return 0;
}
