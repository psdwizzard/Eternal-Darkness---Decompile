extern volatile unsigned int lbl_8032A578;
extern unsigned char lbl_8032B694[];

int fn_800F564C(unsigned char value)
{
    lbl_8032B694[lbl_8032A578++] = value;
    return 0;
}
