typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct EdgeLoop {
    unsigned short count;
    unsigned short unused;
    unsigned short* indices;
} EdgeLoop;

typedef struct Surface {
    unsigned char unused[0x28];
    unsigned short count;
    unsigned short unused2;
    unsigned short* indices;
    signed char inner_count;
    unsigned char unused3[3];
    EdgeLoop* inner;
} Surface;

extern void fn_80179DB0(float*, short*);
extern void fn_8013C264(const Vec3*, const Vec3*, Vec3*, const Vec3*, Vec3*);
extern float fn_80211D4C(const Vec3*, const Vec3*);
extern float lbl_80650318;

float fn_8013C068(const Vec3* point, const Surface* surface,
                  const short* vertices, Vec3* result)
{
    Vec3 first, second, closest, direction;
    float best;
    unsigned int i;
    unsigned int j;
    unsigned char face;
    EdgeLoop* loop;

    loop = surface->inner;
    best = lbl_80650318;
    fn_80179DB0(&first.x, (short*)((char*)vertices + surface->indices[0] * 6));
    for (i = 0; (unsigned short)i < surface->count; i++) {
        unsigned short next = (unsigned short)(i + 1);
        float distance;
        if (next >= surface->count)
            next = 0;
        fn_80179DB0(&second.x, (short*)((char*)vertices + surface->indices[next] * 6));
        fn_8013C264(&first, &second, &direction, point, &closest);
        distance = fn_80211D4C(point, &closest);
        if (distance < best) {
            best = distance;
            *result = closest;
        }
        first = second;
    }

    for (face = 0; face < surface->inner_count; face++, loop++) {
        fn_80179DB0(&first.x, (short*)((char*)vertices + loop->indices[0] * 6));
        for (j = 0; (unsigned short)j < loop->count; j++) {
            unsigned short next = (unsigned short)(j + 1);
            float distance;
            if (next >= loop->count)
                next = 0;
            fn_80179DB0(&second.x, (short*)((char*)vertices + loop->indices[next] * 6));
            fn_8013C264(&first, &second, &direction, point, &closest);
            distance = fn_80211D4C(point, &closest);
            if (distance < best) {
                best = distance;
                *result = closest;
            }
            first = second;
        }
    }
    return best;
}
