extern unsigned char lbl_805E27DC[];
extern void OSSendMessage(void*, int, int);

void fn_8015C020(int value)
{
    OSSendMessage(lbl_805E27DC, value, 1);
}
