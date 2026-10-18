typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

extern float sinf(float);
extern float cosf(float);
extern float lbl_80650868;

void fn_80179F48(const Vec4* input, Vec4* output)
{
    float angle = input->w * lbl_80650868;
    float scale = sinf(angle);

    output->w = cosf(angle);
    output->x = scale * input->x;
    output->y = scale * input->y;
    output->z = scale * input->z;
}
