extern unsigned char lbl_805B6FFC[];
extern unsigned char lbl_805E27DC[];
extern unsigned char lbl_805DB240[];

extern void OSSendMessage(void*, int, int);
extern int OSReceiveMessage(void*, unsigned int*, int);

void fn_8015CB00(int mode)
{
    int i = 0;

    if (mode == 1) {
        unsigned int message;

        OSSendMessage(lbl_805B6FFC, -1, 1);
        OSSendMessage(lbl_805E27DC, -1, 1);
        do {
            OSReceiveMessage(lbl_805DB240, &message, 1);
            i++;
        } while (i < 2);
    } else {
        OSSendMessage(lbl_805B6FFC, -2, 1);
        OSSendMessage(lbl_805E27DC, -2, 1);
    }
}
