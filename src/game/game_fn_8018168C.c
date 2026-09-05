typedef signed short s16;

typedef struct Coord {
    s16 x;
    s16 y;
} Coord;

typedef struct Entry {
    unsigned char pad[10];
    Coord position;
} Entry;

extern s16 lbl_80606360[];

void fn_8018168C(Entry* dst, const Coord* src, s16 angle, int scale)
{
    int index = angle;
    dst->position.x = src->x + ((lbl_80606360[index] * scale) >> 7);
    dst->position.y = src->y + ((lbl_80606360[index + 0x40] * scale) >> 7);
}
