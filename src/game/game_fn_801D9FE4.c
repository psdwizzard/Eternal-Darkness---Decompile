typedef signed short s16;
typedef unsigned int u32;

extern int fn_801DA0A0(u32);
extern float fn_8010181C(float);

int fn_801D9FE4(u32 value, s16 amount)
{
    int divisor = fn_801DA0A0(value);
    float numerator = (float)amount;
    float denominator = (float)divisor;
    int result = (int)fn_8010181C(numerator / denominator);
    return result;
}
