typedef unsigned int u32;

extern u32 synthInfo[];
extern float lbl_80651028;
extern u32 fn_800F5C54(float);

u32 hwFrq2Pitch(u32 value)
{
    return fn_800F5C54(lbl_80651028 * (float)value / (float)synthInfo[0]);
}
