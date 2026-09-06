typedef unsigned int u32;

extern int fn_801D38E8(int);
extern u32 lbl_802557EC[];

u32 fn_801D39F4(int value)
{
    return lbl_802557EC[fn_801D38E8(value)];
}
