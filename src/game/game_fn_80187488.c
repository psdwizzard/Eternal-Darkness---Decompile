typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 pad[0xA];
    s16 coordinate[3];
    u8 tail[0x28];
} Entry;

#pragma use_lmw_stmw on

extern int fn_800FBFB0(void);

void fn_80187488(Entry* entry, u16* flags, s16* bounds, int axis, int start,
                 int end, s16* first, s16* second, int add, int delta)
{
    s16* bound;
    int a = second[axis];
    int b = first[axis];
    int peak;
    int step;
    int current;
    int index;
    u32 mask;

    if (a > b) {
        peak = add + a;
    } else {
        peak = add + b;
    }
    step = (2 * peak - b - a) / (end - start);
    current = b;
    index = start;
    mask = 1 << (start + 3);
    bound = &bounds[start];
    while (index < end) {
        int hit = 0;
        if ((*flags & mask) != 0) {
            entry->coordinate[axis] += delta;
            if (entry->coordinate[axis] >= *bound) hit = 1;
        } else {
            entry->coordinate[axis] -= delta;
            if (entry->coordinate[axis] <= *bound) hit = 1;
        }
        if (hit) {
            int value;
            entry->coordinate[axis] = *bound;
            value = fn_800FBFB0() % step;
            if (step < 0) value = -value;
            *bound = (s16)(current + value);
            if (entry->coordinate[axis] < *bound) *flags |= mask;
            else *flags &= ~mask;
        }
        current += step;
        if (current > peak) step = -step;
        mask <<= 1;
        entry++;
        bound++;
        index++;
    }
}
