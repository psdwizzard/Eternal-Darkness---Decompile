typedef struct Vec3_800930B0 {
    float x, y, z;
} Vec3_800930B0;

extern Vec3_800930B0 lbl_80239688;
extern int fn_80201EB8();
extern void fn_800453E8(void*, void*, void*, void*, float, int, int, void*, int,
                        Vec3_800930B0*, int, void*);
extern const float lbl_8064EC7C;

void fn_800930B0(register void* arg1, register void* arg2,
                 register void* arg3, register void* arg4,
                 register void* arg5)
{
    Vec3_800930B0 direction = lbl_80239688;
    void* runtime = (void *)fn_80201EB8(arg1);

    fn_800453E8(arg3, arg2, runtime, arg4, lbl_8064EC7C, 0, 0, arg5, 0x5B,
                &direction, 3, arg1);
}
