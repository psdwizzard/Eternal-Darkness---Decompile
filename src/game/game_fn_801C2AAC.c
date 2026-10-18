extern float lbl_80650F60;
extern float lbl_80650F64;
extern float lbl_80650F68;

extern float fn_800F5C54(float);
extern float powf(float, float);

float adsrConvertTimeCents(int value)
{
    return fn_800F5C54(lbl_80650F60 * powf(lbl_80650F64, lbl_80650F68 * value));
}
