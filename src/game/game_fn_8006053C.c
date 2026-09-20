typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;

#pragma use_lmw_stmw on

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct OwnerData {
    u8 pad00[0x90];
    void *range;
} OwnerData;

typedef struct RangeData {
    u8 pad00[0x2C];
    s8 low;
    u8 pad2D[7];
    s8 middle;
    u8 pad35[7];
    s8 high;
} RangeData;

extern unsigned int fn_800FBFB0(void);
#define fn_800FBFB0() ((int)fn_800FBFB0())
extern void *fn_80201B8C();
extern void *fn_80201BC8();
extern void fn_800360B0(void *, u16 *);
extern RangeData *fn_80072354(void *);
extern void fn_8011F114();
extern s32 fn_80066D04(void *, s32);

s32 fn_8006053C(void *owner, s32 enabled)
{
    s32 value = fn_800FBFB0() % 100;
    OwnerData *owner_data = fn_80201B8C(owner);
    void *resource = fn_80201BC8(owner);
    u16 flags;
    s32 select;
    RangeData *range;
    Vec3 position;
    s32 low;
    s32 middle;
    s32 high;

    fn_800360B0(owner, &flags);
    select = enabled & ~(-((flags >> 7) & 1));
    range = fn_80072354(owner_data->range);
    fn_8011F114(&position, resource);

    low = range->low;
    middle = range->middle;
    high = range->high;
    middle += low;
    high += middle;

    if (fn_80066D04(owner, 3) == 0) {
        select = 0;
        flags |= 1;
    }
    if (fn_80066D04(owner, 2) == 0) {
        select = 0;
        flags |= 2;
    }

    value = (flags & 1) ? (s8)middle : value;
    if (flags & 2) {
        if (flags & 1) {
            if (select != 0) {
                value = (s8)high;
            } else {
                value = (s8)high + 1;
            }
        } else {
            value = low;
        }
    }

    if (value <= low) {
        return 4;
    }
    if (value <= (s8)middle) {
        return 5;
    }
    if (value <= (s8)high) {
        return 6;
    }
    return -1;
}
