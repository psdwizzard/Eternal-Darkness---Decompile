typedef struct ShortCoord3 {
    short x;
    short y;
    short z;
} ShortCoord3;

extern float sinf(float);
extern float cosf(float);

void fn_80179398(ShortCoord3* input, ShortCoord3* output, float angle)
{
    float sin_angle = sinf(angle);
    float cos_angle = cosf(angle);

    output->x = (short)(input->x * cos_angle - input->y * sin_angle);
    output->y = (short)(input->x * sin_angle + input->y * cos_angle);
    output->z = input->z;
}
