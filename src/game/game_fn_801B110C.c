extern void __DTKStartAi(void);
extern void DVDStopStreamAtEndAsync(void*, int);
extern void __DTKCheckUserCallback(void*, unsigned int);
extern char __block_for_run_callback[];
extern int __DTKState;
extern void* __DTKCurrentTrack;

void __DTKCallbackForRun(void)
{
    __DTKStartAi();
    DVDStopStreamAtEndAsync(__block_for_run_callback, 0);
    __DTKState = 1;
    __DTKCheckUserCallback(__DTKCurrentTrack, 1);
}
