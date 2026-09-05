typedef unsigned int u32;

extern u32 lbl_80619C20[];
extern float lbl_80651028;
extern void fn_800F5C54(float);

void fn_801CD228(u32 value)
{
    fn_800F5C54(lbl_80651028 * (float)lbl_80619C20[0] / (float)value);
}
