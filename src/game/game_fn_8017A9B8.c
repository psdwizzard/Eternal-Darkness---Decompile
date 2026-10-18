typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

extern float fn_8003315C(float);
extern float sinf(float);
extern const float lbl_8065086C;
extern const double lbl_806508A8;

void fn_8017A9B8(const Vec4* left, const Vec4* right, float amount,
                 Vec4* output, int turns)
{
    float angle = fn_8003315C(left->x * right->x + left->y * right->y +
                             left->z * right->z + left->w * right->w);
    float sine = sinf(angle);
    float offset = amount * (angle + lbl_8065086C * turns);
    float left_scale = sinf(angle - offset) / sine;
    float right_scale = sinf(offset) / sine;

    output->x = left_scale * left->x + right_scale * right->x;
    output->y = left_scale * left->y + right_scale * right->y;
    output->z = left_scale * left->z + right_scale * right->z;
    output->w = left_scale * left->w + right_scale * right->w;
}
