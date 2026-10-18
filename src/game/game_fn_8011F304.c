typedef unsigned char u8;

typedef float Matrix[3][4];
typedef float Vec3[3];

typedef struct TransformOutput {
    u8 pad[8];
    Vec3 first;
    Vec3 second;
    u8 pad2[4];
    u8 enabled;
} TransformOutput;

extern void PSMTXMultVec(Matrix matrix, Vec3 input, Vec3 output);
extern float lbl_80650068;

void fn_8011F304(TransformOutput* output, Matrix matrix, int enabled)
{
    float x;
    float y;
    float z;
    float zero;

    output->enabled = enabled;
    PSMTXMultVec(matrix, output->first, output->first);
    x = matrix[0][3];
    y = matrix[1][3];
    z = matrix[2][3];
    zero = lbl_80650068;
    matrix[0][3] = zero;
    matrix[1][3] = zero;
    matrix[2][3] = zero;
    PSMTXMultVec(matrix, output->second, output->second);
    matrix[0][3] = x;
    matrix[1][3] = y;
    matrix[2][3] = z;
}
