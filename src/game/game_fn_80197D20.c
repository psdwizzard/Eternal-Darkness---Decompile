typedef signed short s16;
typedef unsigned char u8;

typedef struct ShortCoord3 { s16 x; s16 y; s16 z; } ShortCoord3;
typedef struct Vec3 { float x; float y; float z; } Vec3;
extern Vec3 lbl_8023B0A0;
extern float lbl_80650B94;
extern float lbl_80650BA8;
extern float lbl_80650BAC;
extern void fn_8018FEDC(u8*, u8*, int, ShortCoord3*, int);
extern void fn_80198AAC(void*, void*, void*, int, int, void*, int);
extern float fn_80179370(float, float, float, float);
extern void fn_80198154(void*, void*, int, Vec3*, Vec3*);
extern void fn_80198318(void*, int, int, void*, int, int);
extern void fn_80198BF4(void*, float);
extern void* memcpy(void*, const void*, unsigned long);

void fn_80197D20(u8* object, u8* vertices, void* info, u8 flags)
{
    ShortCoord3 position;
    Vec3 direction;
    Vec3 initial = lbl_8023B0A0;
    register void* info_local = info;
    u8 count = object[1];
    int half_count = (count >> 1) & 0x7f;
    u8* entry = *(u8**)(object + 0x4c);
    u8 flags_local = flags;
    u8* vertices_local = vertices;
    u8* object_local = object;
    int vertex_offset;
    register u8* saved_entry = entry;
    int index;
    int generated;
    register int saved_half_count = object[1] >> 1;
    register int full_count = object[1];

    generated = 0;
    index = 0;
    vertex_offset = 0;
    while (index < count) {
        u8* destination = vertices_local + vertex_offset;
        if (index < half_count) {
            fn_8018FEDC(object_local, destination, index,
                        (ShortCoord3*)info_local, saved_half_count);
        } else {
            fn_80198AAC(object_local + 0xa0, saved_entry, destination, index,
                        generated, info_local, full_count);
            generated++;
        }
        saved_entry += 0x38;
        vertex_offset += 0xc;
        index++;
    }

    memcpy(&position, object_local + 0x16, 6);
    direction.x = lbl_80650BA8;
    direction.y = lbl_80650B94;
    direction.z = fn_80179370((float)position.y, (float)position.x,
                              direction.y, direction.x);
    fn_80198154(object_local + 0x10, vertices_local, object_local[1] * 2,
                &initial, &direction);

    for (index = 0; index < count; index++) {
        ShortCoord3* first =
            (ShortCoord3*)(vertices_local + (index << 1) * 6);
        ShortCoord3* delta =
            (ShortCoord3*)(entry + index * 0x38 + 0x10);
        delta->x = first[1].x - first[0].x;
        delta->y = first[1].y - first[0].y;
        delta->z = first[1].z - first[0].z;
    }

    fn_80198318(entry, half_count, count, vertices_local, count, 2);
    if (flags_local & 0x80) {
        for (index = 0; index < count; index++)
            fn_80198BF4(entry + index * 0x38 + 0x10, lbl_80650BAC);
    }
}
