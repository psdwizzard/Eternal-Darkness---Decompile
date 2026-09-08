typedef unsigned int u32;

extern u32 lbl_8064C360;

void fn_801E9124(u32* value)
{
    u32 remainder;
    if ((remainder = *value % lbl_8064C360) != 0) {
        *value += lbl_8064C360 - remainder;
    }
}
