typedef unsigned char u8;

extern int fn_801A9B94(int, int);
extern void DTKSetVolume(int, int);
extern int lbl_8064D2F8;
extern int lbl_8064D2F9;

void fn_801ACCA0(int first, int second)
{
    int first_value = fn_801A9B94(first, 3);
    int second_value = fn_801A9B94(second, 3);

    *(u8*)&lbl_8064D2F9 = first;
    *(u8*)&lbl_8064D2F8 = second;
    DTKSetVolume(first_value, second_value);
}
