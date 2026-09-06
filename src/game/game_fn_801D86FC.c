typedef unsigned char u8;

extern const float lbl_806510EC;
extern const float lbl_806510F4;

float fn_801D86FC(u8 value)
{
    float result = lbl_806510EC;

    if (!(value & 6)) {
        result = lbl_806510F4;
    }
    return result;
}
