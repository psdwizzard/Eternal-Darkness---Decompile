typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Coord2 {
    float x;
    float y;
} Coord2;

typedef struct Coord3 {
    float x;
    float y;
    float z;
} Coord3;

extern void fn_80179CD4(Coord2*, const Coord3*, float, float, float, s8);

u8 fn_8013D260(const Coord3* point, const Coord2* vertices, u16 count,
                int axis, float first, float second, float third)
{
    Coord2 projected;
    u8 inside = 0;
    const Coord2* current;
    int i;
    int previous;

    fn_80179CD4(&projected, point, first, second, third, (s8)axis);
    current = vertices;
    previous = count - 1;
    for (i = 0; i < count; i++, current++) {
        float y = current->y;
        if ((y <= projected.y && projected.y < vertices[previous].y) ||
            (vertices[previous].y <= projected.y && projected.y < y)) {
            float x = current->x;
            if (projected.x < x + ((projected.y - y) *
                (vertices[previous].x - x)) / (vertices[previous].y - y)) {
                inside = !inside;
            }
        }
        previous = i;
    }
    return inside;
}
