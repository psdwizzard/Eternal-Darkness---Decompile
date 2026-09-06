typedef signed short s16;
typedef unsigned int u32;

extern u32 lbl_802557CC[];
extern s16 lbl_802557E0[];

void fn_801D38BC(int index, u32* value, s16* number)
{
    *value = lbl_802557CC[index];
    *number = lbl_802557E0[index];
}
