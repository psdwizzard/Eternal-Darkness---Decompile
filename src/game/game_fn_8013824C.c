extern int OSReceiveMessage(void*, void*, int);
extern void OSSendMessage(void*, void*, int);
typedef struct Queue { unsigned char data[0x20]; } Queue;
extern Queue lbl_805ADFE0;
extern Queue lbl_805AE000;

void fn_8013824C(void)
{
    while (OSReceiveMessage(&lbl_805AE000, 0, 0) != 0) {
        OSSendMessage(&lbl_805ADFE0, 0, 0);
    }
}
