typedef unsigned char u8;
extern u8 lbl_805B40A0[];
extern int lbl_8064D040;
extern int lbl_8064D044;
extern void PADControlMotor(int, int);
extern void* memset(void*, int, unsigned int);

void fn_80144178(void)
{
    PADControlMotor(0, 2);
    memset(lbl_805B40A0, 0, 0x1E);
    lbl_8064D044 = 0;
    lbl_8064D040 = 0;
}
