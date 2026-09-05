extern const float lbl_80650DBC;
extern const float lbl_80650DC0;
extern const float lbl_80650DC4;

float fn_801A657C(int value)
{
    float result;

    result = lbl_80650DBC;
    if (value >= 25) {
        result = lbl_80650DC0 * (float)value + result - lbl_80650DC4;
    }
    return result;
}
