typedef int s32;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

#pragma use_lmw_stmw on

extern const Vec3 lbl_80238CF4;
extern double lbl_8064E038;
extern float lbl_8064E064;
extern float lbl_8064E068;

extern void fn_8012CEA4(void*, s32, Vec4*);
extern unsigned int rand(void);
#define rand() ((int)rand())
extern void fn_8017A244(Vec3*, Vec4*, float);
extern void fn_8012CF08(void*, s32, Vec4, Vec4, s32, s32, float);
extern void fn_8012F58C(void*, s32, s32, s32, s32, s32);
extern void fn_8012D0D0(void*);

void fn_8002BFE0(void* object)
{
    float scale;
    s32 random;
    Vec4 second;
    Vec4 first;
    Vec3 direction = lbl_80238CF4;
    s32 i;
    float* component = &direction.x;

    for (i = 0; i < 3; i++, component++) {
        fn_8012CEA4(object, 0xF, &first);
        random = (rand() & 0xF) + 10;
        scale = (float)random;
        scale = 1.0f / scale;
        *component = 1.0f;
        fn_8017A244(&direction, &second, scale);
        fn_8012CF08(object, 0xF, first, second, 0, 1, scale);
        *component = 0.0f;
        fn_8012F58C(object, 0xF, 3, 0, 0, 0x20);
        fn_8012D0D0(object);
    }
}
