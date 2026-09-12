typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void *fn_80201BC8(void *object);
extern u8 fn_8012B8A8(void *transform, const Vec3 *position);

u8 fn_80204578(void *object, const Vec3 *position)
{
    return fn_8012B8A8(fn_80201BC8(object), position);
}
