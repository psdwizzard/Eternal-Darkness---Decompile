typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

extern float PSVECSquareMag(const Vec4*);

#pragma opt_common_subs off
#pragma optimization_level 2
float fn_8017A65C(const Vec4* value)
{
    float length = PSVECSquareMag(value);
    return length + value->w * value->w;
}
#pragma opt_common_subs reset
#pragma optimization_level reset
