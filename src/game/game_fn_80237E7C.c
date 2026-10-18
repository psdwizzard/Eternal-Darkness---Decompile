typedef struct OSMessageQueue OSMessageQueue;

extern OSMessageQueue lbl_80648178;
extern int OSSendMessage(OSMessageQueue *queue, void *message, int flags);

void fn_80237E7C(int result)
{
    OSSendMessage(&lbl_80648178, (void *)result, 1);
}
