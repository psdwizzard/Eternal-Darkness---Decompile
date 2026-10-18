extern char lbl_805B6FFC[];
extern void OSSendMessage(void*, unsigned int, int);

void fn_80159DD0(unsigned int value, unsigned int shift)
{
    OSSendMessage(lbl_805B6FFC, (value | 0x80000000) | (shift << 12), 1);
}
