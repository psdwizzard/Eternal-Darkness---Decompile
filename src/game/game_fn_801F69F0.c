typedef struct Int3 {
    int x;
    int y;
    int z;
} Int3;

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

typedef struct Matrix44 {
    float m[4][4];
} Matrix44;

extern Matrix44 lbl_8063BF28;
extern Matrix44 lbl_8063C028;
extern Matrix44 lbl_8063C098;

extern int fn_801A93E8(int, int);
extern float fn_8017AE0C(const Matrix44*, float);
extern void fn_8017ACE0(const Matrix44*, const Vec3*, Vec3*);

void fn_801F69F0(const Int3* input, Vec3* output, int shift)
{
    Vec4 normalized;
    Vec3 transformed;
    int adjusted_x = fn_801A93E8(input->x, shift);
    int scale = 1 << shift;

    normalized.x = 2.0f * (float)adjusted_x / (float)(scale * 640) -
                   1.0f;
    normalized.y = 1.0f -
                   2.0f * (float)input->y / (float)(scale * 480);
    normalized.z = ((float)input->z - 16352.0f) / 16352.0f;

    normalized.w = fn_8017AE0C(&lbl_8063BF28, normalized.z);
    normalized.x *= normalized.w;
    normalized.y *= normalized.w;
    normalized.z *= normalized.w;

    fn_8017ACE0(&lbl_8063C028, (Vec3*)&normalized, &transformed);
    transformed.z = lbl_8063C028.m[3][2] * normalized.w;
    fn_8017ACE0(&lbl_8063C098, &transformed, output);
}
