typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

extern float fn_8017A574(const Vec4*, const Vec4*);
extern float fn_8003315C(void);
extern const float lbl_80650860;
extern const float lbl_80650878;
extern const float lbl_806508CC;

float fn_8017A5A8(const Vec4* left, const Vec4* right, float limit)
{
    float result = lbl_80650878;
    float dot = fn_8017A574(left, right);
    float magnitude;

    if (dot < lbl_80650860) {
        magnitude = -dot;
    } else {
        magnitude = dot;
    }

    if (lbl_80650878 - magnitude > lbl_806508CC) {
        float random = fn_8003315C();
        if (random > limit) {
            result = limit / random;
        }
    }

    return result;
}
