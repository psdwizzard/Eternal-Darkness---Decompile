typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

extern float fn_8003315C(float);
extern float sinf(float);
extern const float lbl_80650870;
extern const float lbl_80650878;

void fn_8017A7D4(const Vec4* left, const Vec4* right, float amount,
                 Vec4* output)
{
    float left_y = left->y;
    float right_y;
    float dot = left->x * right->x + left_y * (right_y = right->y) +
                left->z * right->z + left->w * right->w;
    float left_scale;
    float right_scale;

    if (1.0 + dot > 0.01f) {
        if (1.0 - dot > 0.01f) {
            float angle = fn_8003315C(dot);
            float sine = sinf(angle);
            float offset = amount * angle;
            left_scale = sinf(angle - offset) / sine;
            right_scale = sinf(offset) / sine;
        } else {
            right_scale = amount;
            left_scale = lbl_80650878 - amount;
        }

        output->x = left_scale * left->x + right_scale * right->x;
        output->y = left_scale * left->y + right_scale * right->y;
        output->z = left_scale * left->z + right_scale * right->z;
        output->w = left_scale * left->w + right_scale * right->w;
    } else {
        output->x = -right_y;
        output->y = right->x;
        left_scale = lbl_80650870 * amount;
        output->z = -right->w;
        right_scale = lbl_80650870 - left_scale;
        output->w = right->z;

        right_scale = sinf(right_scale);
        left_scale = sinf(left_scale);
        output->x = right_scale * left->x + left_scale * output->x;
        output->y = right_scale * left->y + left_scale * output->y;
        output->z = right_scale * left->z + left_scale * output->z;
        output->w = right_scale * left->w + left_scale * output->w;
    }
}
