typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct { u8 pad[0xA]; s16 value[23]; } Entry;

#pragma use_lmw_stmw on

extern void fn_80186C88(s16* output, int count, int step, int base, int magnitude);

void fn_801871F0(u8* entry, u16* flags, s16* bounds, int axis, int start,
                 int end, int base, int step, int magnitude, int delta)
{
    int offset;
    int index;
    u32 mask;

    index = start;
    mask = 1 << (start + 3);
    offset = axis;

    while (index < end) {
        s16* bound = &bounds[index];
        int hit = 0;
        if ((*flags & mask) != 0) {
            ((Entry*)entry)->value[offset] += delta;
            if (((Entry*)entry)->value[offset] >= *bound) {
                hit = 1;
            }
        } else {
            ((Entry*)entry)->value[offset] -= delta;
            if (((Entry*)entry)->value[offset] <= *bound) {
                hit = 1;
            }
        }
        if (hit) {
            ((Entry*)entry)->value[offset] = *bound;
            fn_80186C88(bound, 1, step, base, magnitude);
            if (((Entry*)entry)->value[offset] < *bound) {
                *flags |= mask;
            } else {
                *flags &= ~mask;
            }
        }
        base += step;
        mask <<= 1;
        entry += 0x38;
        index++;
    }
}
