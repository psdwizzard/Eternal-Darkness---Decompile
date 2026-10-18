typedef signed short s16;
typedef unsigned char u8;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef float Matrix34[3][4];

extern float lbl_80650BB0;
extern void PSMTXRotRad(Matrix34, int, float);
extern void PSMTXConcat(Matrix34, Matrix34, Matrix34);
extern void PSMTXMultVec(Matrix34, Vec3*, Vec3*);

void fn_80198154(s16* source, s16* destination, u8 count, void* unused,
                 Vec3* rotation)
{
    Vec3 transformed;
    Matrix34 transform;
    Matrix34 x_rotation;
    Matrix34 y_rotation;
    Matrix34 z_rotation;
    Matrix34 result;
    int index;

    PSMTXRotRad(x_rotation, 0x78, lbl_80650BB0 * rotation->x);
    PSMTXRotRad(y_rotation, 0x79, lbl_80650BB0 * rotation->y);
    PSMTXRotRad(z_rotation, 0x7A, lbl_80650BB0 * rotation->z);
    PSMTXConcat(z_rotation, y_rotation, result);
    PSMTXConcat(result, x_rotation, transform);

    index = 0;
    while (index < count) {
        transformed.x = (float)destination[0];
        transformed.y = (float)destination[1];
        transformed.z = (float)destination[2];
        PSMTXMultVec(transform, &transformed, &transformed);
        destination[0] = (s16)((float)source[0] + transformed.x);
        destination[1] = (s16)((float)source[1] + transformed.y);
        destination[2] = (s16)((float)source[2] + transformed.z);
        destination += 3;
        index++;
    }
}
