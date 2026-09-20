typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad[0xA];
    s16 coordinate[3];
    u8 rest[0x28];
} Entry;

#pragma use_lmw_stmw on

extern int fn_800FBFB0(void);

void fn_801875FC(Entry* entry, u16* flags, s16* bounds, int axis, int start,
                 int end, s16* first, s16* second, int add, int delta)
{
    int a;
    int b;
    int peak;
    float step;
    int step_integer;
    float current;
    int index;
    u32 mask;

    a = second[axis];
    b = first[axis];
    if (a > b) {
        peak = add;
        peak += a;
    } else {
        peak = add + b;
    }
    step = (float)(2 * peak - b - a) / (float)(end - start);
    step_integer = (int)step;
    current = (float)b;
    index = start;
    mask = 1 << (start + 3);
    while (index < end) {
        int hit = 0;
        if ((*flags & mask) != 0) {
            entry->coordinate[axis] += delta;
            if (entry->coordinate[axis] >= bounds[index]) hit = 1;
        } else {
            entry->coordinate[axis] -= delta;
            if (entry->coordinate[axis] <= bounds[index]) hit = 1;
        }
        if (hit) {
            int value;
            entry->coordinate[axis] = bounds[index];
            value = fn_800FBFB0() % step_integer;
            if (step < 0.0f) value = -value;
            bounds[index] = (s16)(current + (float)value);
            if (entry->coordinate[axis] < bounds[index]) *flags |= mask;
            else *flags &= ~mask;
        }
        current += step;
        if (current > (float)peak) step = -step;
        mask <<= 1;
        entry++;
        index++;
    }
}
