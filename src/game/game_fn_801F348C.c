typedef unsigned long u32;

extern u32 lbl_8064C384;
extern u32 lbl_8064D764;

void fn_801F348C(u32* value, u32 duration)
{
    u32 saved = *value;
    lbl_8064D764 = duration;
    lbl_8064C384 = saved;
}
