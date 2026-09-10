typedef unsigned int u32;

extern u32 lbl_80619C20[];
extern float lbl_80651028;
extern u32 fn_800F5C54(float);

u32 fn_801CD228(u32 value)
{
    return fn_800F5C54(lbl_80651028 * (float)value / (float)lbl_80619C20[0]);
}
