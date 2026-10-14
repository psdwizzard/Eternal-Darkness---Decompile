typedef struct OSMessageQueue OSMessageQueue;

extern OSMessageQueue lbl_80648178;
extern int fn_8020D250(OSMessageQueue *queue, void *message, int flags);

void fn_80237E7C(int result)
{
    fn_8020D250(&lbl_80648178, (void *)result, 1);
}
