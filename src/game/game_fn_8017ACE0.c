typedef struct Matrix44 Matrix44;
typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void PSMTXMultVec(const Matrix44* matrix, const Vec3* input, Vec3* output);

void fn_8017ACE0(const Matrix44* matrix, const Vec3* input, Vec3* output)
{
    PSMTXMultVec(matrix, input, output);
}
