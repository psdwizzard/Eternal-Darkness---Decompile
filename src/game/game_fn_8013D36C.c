typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;

typedef struct Coord2 {
    float x;
    float y;
} Coord2;

typedef struct Coord3 {
    float x;
    float y;
    float z;
} Coord3;

typedef struct ShortCoord2 {
    short x;
    short y;
} ShortCoord2;

typedef struct ShortCoord3 {
    short x;
    short y;
    short z;
} ShortCoord3;

extern void fn_80179CD4(Coord2*, const Coord3*, float, float, float, s8);
extern void fn_80179D78(short*, const short*, s8);

u8 fn_8013D36C(const Coord3* point, u16 count, const u16* indices,
               const ShortCoord3* vertices, float unused_first, float unused_second,
               float unused_third, int axis)
{
    Coord2 projected;
    ShortCoord2 current;
    ShortCoord2 previous;
    s8 selected_axis = axis;
    u16 i;
    u8 inside = 0;

    /* The projection helper ignores these three forwarded float arguments. */
    fn_80179CD4(&projected, point, unused_first, unused_second,
                  unused_third, selected_axis);
    fn_80179D78(&previous.x, &vertices[indices[count - 1]].x, selected_axis);

    for (i = 0; i < count; i++) {
        fn_80179D78(&current.x, &vertices[indices[i]].x, selected_axis);
        if (((float)current.y <= projected.y && projected.y < (float)previous.y) ||
            ((float)previous.y <= projected.y && projected.y < (float)current.y)) {
            float intersection = (float)current.x +
                (float)(previous.x - current.x) *
                (projected.y - (float)current.y) /
                (float)(previous.y - current.y);
            if (projected.x < intersection) {
                inside = !inside;
            }
        }
        previous.x = current.x;
        previous.y = current.y;
    }
    return inside;
}
