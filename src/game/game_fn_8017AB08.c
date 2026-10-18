typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern float sinf(float);
extern float cosf(float);

void fn_8017AB08(const Vec3* input, Vec3* output, float angle)
{
    float sine = sinf(angle);
    float cosine = cosf(angle);

    output->x = input->x * cosine - input->y * sine;
    output->y = input->x * sine + input->y * cosine;
    output->z = input->z;
}
