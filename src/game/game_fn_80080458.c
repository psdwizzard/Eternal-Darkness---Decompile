typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern int lbl_8064D18C;
extern const float lbl_8064EA10;

extern void *fn_80201814();
#define FN_80201E78_RETURN void
#define FN_80201E78_PARAMETERS Vec3 *, void *
extern FN_80201E78_RETURN fn_80201E78(FN_80201E78_PARAMETERS);extern void fn_801AAE68(float, int, int, int, Vec3 *, int, int, int, u32, int);

void fn_80080458(int object, u8 enabled)
{
    Vec3 position;

    if (enabled) {
        void *source = fn_80201814(object);
        fn_80201E78(&position, source);
        fn_801AAE68(lbl_8064EA10, 0x1D2, 0x7D, 0, &position, 2, 1, 0,
                    (u32)lbl_8064D18C & 0xFFFF, 0);
    }
}
