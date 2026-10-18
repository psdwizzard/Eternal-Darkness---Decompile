extern unsigned char lbl_8032EA10[];
extern void OSSendMessage(void*, int, int);

void fn_80108BD4(int status)
{
    if (status == -1) {
        OSSendMessage(lbl_8032EA10, 6, 0);
    } else {
        OSSendMessage(lbl_8032EA10, 1, 0);
    }
}
