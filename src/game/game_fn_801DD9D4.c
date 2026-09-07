typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { float x, y, z; } Vec3;

extern void fn_801DF060(void);
extern void* fn_801D0D78();
extern int fn_8015ABD4(int, int);
extern int fn_80054BCC(int);
extern int fn_801DE8B4(void*, int, int, float);
extern void* fn_80201814(int);
extern int fn_80201BC8(void*);
extern u8 lbl_80255888[];
extern void* fn_801E741C(void*);
extern void fn_801F8748(void*, int, int, int, int);
extern void fn_801D0CA4(void*);
extern void fn_801D0E78(void*);

void* fn_801DD9D4(int flags, int value_f8, Vec3* position, float scale,
                  int value_f4, int value_f0, int value_d4, int enable,
                  int setup_arg, int* output)
{
    void* result;

    result = fn_801D0D78(-1, flags, -1, 0, fn_801DF060, 0, 0, 0, 0, 0);
    if (result != 0) {
        u8* p = result;
        *(int*)(p + 0xbc) = 0;
        *(int*)(p + 0xc4) = 0;
        *(int*)(p + 0xd0) = 0;
        *(u16*)(p + 0xdc) = 300;
        *(int*)(p + 0xc8) = 1;
        if (enable != 0 && fn_8015ABD4(2, 2) == 0 &&
            fn_80054BCC(*(int*)(p + 8)) != 0)
            *(int*)(p + 0xcc) = 1;
        else
            *(int*)(p + 0xcc) = 0;
        *(int*)(p + 0xd4) = value_d4;
        *(int*)(p + 0x138) = 0;
        p[0xd8] = 1;
        p[0xd9] = 0;
        *(int*)(p + 0xf8) = value_f8;
        *(Vec3*)(p + 0x114) = *position;
        *(int*)(p + 0x13c) = 0;
        *(int*)(p + 0xf0) = value_f0;
        *(int*)(p + 0xf4) = value_f4;
        if (fn_801DE8B4(result, 1, setup_arg, scale) != 0) {
            if (*(int*)(p + 0xcc) != 0) {
                int object = fn_80201BC8(fn_80201814(*(int*)(p + 0xe0)));
                void* context = fn_801E741C(lbl_80255888);
                fn_801F8748(context, object, 0, 0, 0);
            }
            *output = *(int*)(p + 0xe0);
            fn_801D0CA4(result);
        } else {
            fn_801D0E78(result);
            result = 0;
        }
    }
    return result;
}
