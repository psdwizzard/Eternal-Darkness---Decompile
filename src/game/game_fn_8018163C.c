typedef signed short s16;

typedef struct Coord {
    s16 x;
    s16 y;
    s16 z;
} Coord;

typedef struct Entry {
    unsigned char pad[10];
    Coord position;
} Entry;

extern s16 lbl_80606360[];

void fn_8018163C(Entry* dst, const Coord* src, s16 angle, int scale)
{
    register int x;
    register int index;
    index = angle;
    x = src->x;
    dst->position.x = x + ((lbl_80606360[index] * scale) >> 7);
    dst->position.y = src->y + ((lbl_80606360[index + 0x40] * scale) >> 7);
    dst->position.z = src->z;
}
