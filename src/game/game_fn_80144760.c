typedef struct MaskThresholds {
    unsigned int first;
    unsigned int second;
    short low[4];
    short extra[4];
    short high[4];
} MaskThresholds;

extern MaskThresholds lbl_805B40F0[];
extern unsigned int fn_80144710(unsigned int, int, int);

unsigned int fn_80144760(unsigned int flags, int side, short distance, int index)
{
    MaskThresholds* limits = &lbl_805B40F0[index];
    int result;

    if (distance > 0) {
        if (side == 0) {
            result = limits->second & flags;
            result &= 0xFF00FFFF;

            if ((flags & 0x00010000) && limits->low[0] < -distance && limits->high[0] >= -distance)
                result |= 0x00010000;
            if ((flags & 0x00020000) && limits->low[0] > distance && limits->high[0] <= distance)
                result |= 0x00020000;
            if ((flags & 0x00040000) && limits->low[1] < -distance && limits->high[1] >= -distance)
                result |= 0x00040000;
            if ((flags & 0x00080000) && limits->low[1] > distance && limits->high[1] <= distance)
                result |= 0x00080000;
            if ((flags & 0x00100000) && limits->low[2] < -distance && limits->high[2] >= -distance)
                result |= 0x00100000;
            if ((flags & 0x00200000) && limits->low[2] > distance && limits->high[2] <= distance)
                result |= 0x00200000;
            if ((flags & 0x00400000) && limits->low[3] < -distance && limits->high[3] >= -distance)
                result |= 0x00400000;
            if ((flags & 0x00800000) && limits->low[3] > distance && limits->high[3] <= distance)
                result |= 0x00800000;

            if ((unsigned int)result != 0)
                result |= flags & 0xC0000000;
            return result;
        } else {
            result = limits->first & flags;
            result &= 0xFF00FFFF;

            if ((flags & 0x00010000) && limits->low[0] < -distance)
                result |= 0x00010000;
            if ((flags & 0x00020000) && limits->low[0] > distance)
                result |= 0x00020000;
            if ((flags & 0x00040000) && limits->low[1] < -distance)
                result |= 0x00040000;
            if ((flags & 0x00080000) && limits->low[1] > distance)
                result |= 0x00080000;
            if ((flags & 0x00100000) && limits->low[2] < -distance)
                result |= 0x00100000;
            if ((flags & 0x00200000) && limits->low[2] > distance)
                result |= 0x00200000;
            if ((flags & 0x00400000) && limits->low[3] < -distance)
                result |= 0x00400000;
            if ((flags & 0x00800000) && limits->low[3] > distance)
                result |= 0x00800000;
        }

        if ((unsigned int)result != 0)
            result |= flags & 0xC0000000;
        return result;
    }
    return fn_80144710(flags, side, index);
}
