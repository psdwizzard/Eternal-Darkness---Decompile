typedef struct MaskThresholds {
    unsigned int mask;
    unsigned int other;
    short low[4];
    short extra[4];
    short high[4];
} MaskThresholds;

extern MaskThresholds lbl_805B40F0[];

short fn_80144A2C(unsigned int flags, short adjustment, short scale, int index)
{
    short value = 0;
    MaskThresholds* entry = &lbl_805B40F0[index];
    unsigned int selected = flags & entry->mask;
    short limit = 0x7FFF;
    int product;
    int adjust;

    if (flags & 0x40000000)
        limit = adjustment + 1;
    if (flags == 0)
        value = 0x7FFF;
    if (selected & 0x1F1F)
        value = limit;
    if (selected & 0x10000000) {
        if (entry->mask & 1) {
            value = -limit;
        } else if (entry->mask & 2) {
            value = limit;
        }
    }
    if (selected & 0x20000000) {
        if (entry->mask & 4) {
            value = -limit;
        } else if (entry->mask & 8) {
            value = limit;
        }
    }
    if (selected & 0x01000000)
        value = entry->extra[0];
    if (selected & 0x02000000)
        value = entry->extra[1];
    if (selected & 0x00300000)
        value = entry->low[2];
    if (selected & 0x00C00000)
        value = entry->low[3];
    if (selected & 0x00030000)
        value = entry->low[0];
    if (selected & 0x000C0000)
        value = entry->low[1];
    if ((flags & 0x80000000) && value < 0) {
        value = -value;
    } else if (value < 0) {
        value += adjustment;
        if (value < 0) {
            product = value * scale;
            adjust = product % 0x7FFF != 0;
            if (scale > 0) {
                adjust = -adjust;
            }
            return product / 0x7FFF + adjust;
        }
    }
    if (value > 0) {
        value -= adjustment;
        if (value > 0) {
            product = value * scale;
            adjust = product % 0x7FFF != 0;
            if (scale < 0) {
                adjust = -adjust;
            }
            return product / 0x7FFF + adjust;
        }
    }
    return 0;
}
