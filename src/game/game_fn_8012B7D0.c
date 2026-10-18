extern void PSVECSubtract();
extern float fn_800490E8(float, float);
extern const float lbl_806501D0;

float fn_8012B7D0(const void* a, const void* b)
{
    float value[3];

    PSVECSubtract(b, a, value);
    return lbl_806501D0 + fn_800490E8(value[1], value[0]);
}
