typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef float f32;

typedef struct Vec3f { f32 x, y, z; } Vec3f;
typedef struct ShortCoord3 { s16 x, y, z; } ShortCoord3;

typedef struct PathSource {
    char pad0[0xC];
    Vec3f* points;
} PathSource;

extern void* fn_80201BC8(void*);
extern int fn_80036E50(void*);
extern int fn_80201B54(void*);
extern void fn_8011F114(Vec3f*, void*);
extern void fn_80179B64(Vec3f*, ShortCoord3*);
extern unsigned int fn_800FBFB0(void);
extern void fn_80179570(Vec3f*, Vec3f*, Vec3f*);
extern void fn_8013CCEC(Vec3f*, Vec3f*, ShortCoord3*, int, int);
extern void fn_801AAE68(f32, int, int, int, Vec3f*, int, int, int, u16, int);
extern void* fn_801D5EE8(Vec3f* position, u32 object_id, int first, int second,
                         int type, int spawn_first, int spawn_third, int spawn_second,
                         int value14, int value15, int child14, int child15,
                         int set_4000, int set_8000, int value17, int value18,
                         int child18, int value16, int enable, int value06, u32 flags);
extern void fn_801D38BC(int, u32*, s16*);
extern void fn_80152710(Vec3f*, s16, int, int, int, int, u32*);

extern Vec3f lbl_80239B40;
extern volatile int lbl_8064D18C;
extern const f32 lbl_8064F7D0;
extern const f32 lbl_8064F7D4;
extern const f32 lbl_8064F7D8;

Vec3f fn_800E720C(void* object, PathSource* source)
{
    Vec3f result;
    ShortCoord3 points[4];
    Vec3f position;
    Vec3f target;
    Vec3f offset;
    u32 packed_out;
    u32 packed;
    s16 kind;
    void* actor;
    int i;
    int first;
    int second;
    int id;

    result = lbl_80239B40;
    actor = fn_80201BC8(object);
    if (actor != 0) {
        if (fn_80036E50(object) != 6) {
            first = 0x13;
            second = 0;
        } else {
            first = 0x19;
            second = 1;
        }
        fn_8011F114(&position, actor);
        for (i = 0; i < 4; i++) {
            fn_80179B64(source->points + i + 1, &points[i]);
        }
        offset.x = (f32)(0x100 - (int)(fn_800FBFB0() & 0x1FF));
        offset.y = (f32)(0x100 - (int)(fn_800FBFB0() & 0x1FF));
        offset.z = lbl_8064F7D0;
        fn_80179570(&position, &offset, &target);
        fn_8013CCEC(&result, &target, points, 4, 1);
        id = fn_80201B54(object);
        fn_801AAE68(lbl_8064F7D4, 0xDC, 0x64, 0, &position, 2, 1, 0,
                    (u16)lbl_8064D18C, 0);
        fn_801D5EE8(&result, id, first, second, 0, 0, 0, 4,
                    8, 3, 3, 1, 0, 1, 0x11, 0xA, 5, 0, 1, 0x14, 0x70040);
        if (fn_80036E50(object) != 6) {
            fn_801D5EE8(&result, id, first, 1, 0, 0, 0, 4,
                        8, 3, 3, 1, 0, 1, 0x11, 5, 5, 0, 1, 0x14, 0x70040);
        }
        position.z += lbl_8064F7D8;
        fn_801D38BC(0, &packed_out, &kind);
        packed = packed_out;
        fn_80152710(&result, kind, 0x1E, 4, 0x1E, 5, &packed);
    }
    return result;
}
