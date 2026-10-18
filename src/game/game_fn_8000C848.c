typedef int s32;
typedef signed short s16;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern void fn_800385D0(void*, s32, Vec3s*);
extern void fn_8003877C(void*, s32, Vec3s*);
extern void fn_80038650(void*, s32, s16, s32);
extern void fn_800387FC(void*, s32, s16);
extern float ceil(float);

void fn_8000C848(void* object, s32 index, float scale, s32 unused, s32 alternate)
{
    Vec3s value;

    if (alternate != 0) {
        fn_800385D0(object, index, &value);
    } else {
        fn_8003877C(object, index, &value);
    }

    value.x = (s16)ceil((float)value.x * scale);
    if (alternate != 0) {
        fn_80038650(object, index, value.x, 1);
    } else {
        fn_800387FC(object, index, value.x);
    }
}
