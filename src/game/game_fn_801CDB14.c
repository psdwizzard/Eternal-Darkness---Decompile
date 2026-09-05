typedef unsigned int u32;

extern u32 lbl_8064D4EC;

void fn_801CDB14(void* unused, u32 size)
{
    lbl_8064D4EC -= (size + 31) & ~31;
}
