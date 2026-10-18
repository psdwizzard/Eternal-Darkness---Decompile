extern void __DTKStopAi(void);
extern void DVDStopStreamAtEndAsync(void*, int);
extern void __DTKCheckUserCallback(void*, unsigned int);
extern char __block_for_prep_callback[];
extern int __DTKState;
extern void* __DTKCurrentTrack;

void __DTKCallbackForPreparePaused(void)
{
    __DTKStopAi();
    DVDStopStreamAtEndAsync(__block_for_prep_callback, 0);
    __DTKState = 2;
    __DTKCheckUserCallback(__DTKCurrentTrack, 0x20);
}
