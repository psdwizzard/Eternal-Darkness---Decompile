extern unsigned char lbl_8032EA10[];
extern int lbl_8064CC80;
extern void OSSendMessage(void*, int, int);

void fn_80108478(void)
{
    OSSendMessage(lbl_8032EA10, 4, 0);
    lbl_8064CC80 = 0;
}
