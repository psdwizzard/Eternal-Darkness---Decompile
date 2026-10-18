typedef signed short s16;

typedef struct ShortCoord3 {
    s16 x;
    s16 y;
    s16 z;
} ShortCoord3;

extern float sinf(float);
extern float cosf(float);

void fn_8017E958(ShortCoord3* output, ShortCoord3* input, s16 distance,
                 float angle)
{
    output->x = distance * sinf(angle) + input->x;
    output->y = distance * cosf(angle) + input->y;
    output->z = input->z;
}
