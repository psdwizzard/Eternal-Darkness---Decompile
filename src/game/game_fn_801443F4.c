typedef unsigned char u8;
extern u8 lbl_805B40A0[];
extern void PADControlMotor(int, int);
extern void* memset(void*, int, unsigned int);

void fn_801443F4(void)
{
    PADControlMotor(0, 2);
    memset(lbl_805B40A0, 0, 0x1E);
}
