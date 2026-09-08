typedef unsigned char u8;

extern int lbl_8064D6A4;
extern int lbl_8064D6A8;

void fn_801EC318(u8* data, u8 x, u8 y, u8 value)
{
    int index = value;

    if (index < lbl_8064D6A8)
        lbl_8064D6A8 = index;
    if (index > lbl_8064D6A4)
        lbl_8064D6A4 = index;
    data[x + (y << 8)] = value;
}
