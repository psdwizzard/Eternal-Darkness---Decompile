extern float lbl_80651000;
extern double lbl_80651008;
extern double lbl_80651010;
extern double __frsqrte(double);

static inline float sqrtf(float x)
{
    volatile float y;
    if (x > lbl_80651000) {
        double guess = __frsqrte((double)x);
        guess = lbl_80651008 * guess * (lbl_80651010 - guess * guess * x);
        guess = lbl_80651008 * guess * (lbl_80651010 - guess * guess * x);
        guess = lbl_80651008 * guess * (lbl_80651010 - guess * guess * x);
        y = (float)(x * guess);
        return y;
    }
    return x;
}

float fn_801CA484(float* v)
{
    float len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= len;
    v[1] /= len;
    v[2] /= len;
    return len;
}
