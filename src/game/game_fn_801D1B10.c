typedef signed short s16;
typedef float f32;

extern f32 fn_801D1B7C(int, int, int);
extern f32 fn_801023E4(f32);

int fn_801D1B10(int scale, int arg1, int arg2, int arg3)
{
    f32 value = fn_801D1B7C(arg1, arg2, arg3);
    int result = (int)fn_801023E4((s16)scale * value);
    return result;
}
