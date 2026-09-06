typedef signed short s16;
typedef unsigned int u32;

extern int fn_801DA0A0(u32);
extern u32 fn_801CEB2C(u32);

s16 fn_801DA058(u32 value)
{
    int scale = fn_801DA0A0(value);
    return scale * fn_801CEB2C(value);
}
