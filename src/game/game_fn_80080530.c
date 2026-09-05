typedef unsigned char u8;

extern u8 lbl_8031CD84[];
extern void fn_80154514(void *, int);

int fn_80080530(int index, int mode)
{
    void **slot = (void **)(lbl_8031CD84 + 0x46C) + index;
    int released = 0;

    if (*slot != 0) {
        fn_80154514(*slot, mode);
        *slot = 0;
        released = 1;
    }
    return released;
}
