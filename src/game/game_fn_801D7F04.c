typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Object { u8 bytes[0x40]; } Object;
typedef struct Vec3 { float x, y, z; } Vec3;

extern int lbl_8064D18C;
extern const float lbl_806510D0;
extern void fn_801AAE68(float, int, int, int, Vec3*, int, int, int, u16, int);

void fn_801D7F04(Object* object, int emit)
{
    int* handle = *(int**)(object->bytes + 0x1C);

    if (handle != 0) {
        *handle = 0;
    }
    if (emit != 0 && *(int*)(object->bytes + 0x10) == lbl_8064D18C) {
        fn_801AAE68(lbl_806510D0, 0x28A, 100, 0,
                    (Vec3*)(object->bytes + 0x24), 2, 1, 0,
                    lbl_8064D18C, 0);
    }
}
