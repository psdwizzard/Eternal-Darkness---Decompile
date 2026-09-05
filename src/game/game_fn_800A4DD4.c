typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Mat3 {
    float m[3][3];
} Mat3;

typedef struct Info800A4DD4 {
    u8 pad0[0x68];
    void* handle;
    u8 pad6C[0x206];
    u16 value;
    u8 pad274[0xE];
    u8 state;
} Info800A4DD4;

extern Info800A4DD4* fn_800A1D28(void*);
extern int fn_80201B54();
extern void fn_800A2E5C(Info800A4DD4*, int);
extern void* fn_800CA4B8(void*, int, void*, int, unsigned int*, float (*)[3], void*);
extern const Mat3 lbl_8023972C;

int fn_800A4DD4(void* object, void* context, void* unused, void* callback)
{
    int result = 0;
    unsigned int values[3];
    Mat3 matrix;
    Info800A4DD4* info = fn_800A1D28(object);

    matrix = lbl_8023972C;
    values[0] = info->value;
    values[1] = info->value;
    values[2] = info->value;
    ((void*)fn_80201B54(object));
    info->handle = fn_800CA4B8(object, 5, context, 3, values, matrix.m, callback);
    if (info->handle != 0) {
        fn_800A2E5C(info, 3);
        info->state = 3;
        result = 1;
    }
    return result;
}
