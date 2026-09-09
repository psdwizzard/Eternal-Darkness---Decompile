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

typedef struct Matrix44 {
    float m[4][4];
} Matrix44;

extern Matrix44 lbl_8063BF28;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void fn_801F6BD8(const Vec3* input, Int3* output, int clamp, int shift)
{
    float inverse_z;
    float x;
    float y;
    float z;
    int scale;

    if (-input->z <= 0.0) {
        output->z = 0;
        output->y = 0;
        output->x = 0;
        return;
    }

    inverse_z = 1.0f / -input->z;
    x = inverse_z * (input->x * lbl_8063BF28.m[0][0]);
    y = inverse_z * (input->y * lbl_8063BF28.m[1][1]);
    z = inverse_z * (input->z * lbl_8063BF28.m[2][2] +
                     lbl_8063BF28.m[3][2]);

    if (clamp != 0) {
        x = MIN(1.0f, MAX(x, -1.0f));
        y = MIN(1.0f, MAX(y, -1.0f));
        z = MIN(1.0f, MAX(z, -1.0f));
    }

    scale = 1 << shift;
    output->x = (int)((1.0 + x) * ((float)(scale * 640) * 0.5f));
    output->y = (int)((1.0 - y) * ((float)(scale * 480) * 0.5f));
    output->z = (int)(16352.0 * z + 16352.0);
}
