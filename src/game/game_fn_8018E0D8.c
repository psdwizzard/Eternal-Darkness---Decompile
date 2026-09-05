typedef unsigned char u8;
typedef signed short s16;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern u8 lbl_8063C068[];
extern void fn_80179B08(void*, Vec3*);
extern void fn_8017ACE0(void*, Vec3*, Vec3*);
extern int fn_801F6D90(s16, s16, s16);
extern int fn_8018D1F0(u8, int);

typedef void (*Callback)(void*, float, float, float, float, float);

void fn_8018E0D8(u8* object, void* context, Callback callback)
{
    Vec3 position;
    Vec3 projected;
    unsigned int id;
    int radius;
    float extent;

    fn_80179B08(object + 0xA, &position);
    fn_8017ACE0(lbl_8063C068, &position, &projected);
    id = fn_801F6D90(*(s16*)(object + 0xA), *(s16*)(object + 0xC),
                     *(s16*)(object + 0xE));
    radius = fn_8018D1F0(object[0x21], id);
    extent = radius;
    callback(context, projected.x - extent, projected.y - extent,
             projected.x + extent, projected.y + extent, projected.z);
    if (id >= 255) {
        object[0x2B] = 255;
    } else {
        object[0x2B] = id;
    }
}
