extern void* __DTKCurrentTrack;
extern int __DTKState;

extern void __DTKCheckUserCallback(void*, unsigned int);

void __DTKCallbackForStop(void)
{
    __DTKCheckUserCallback(__DTKCurrentTrack, 2);
    __DTKState = 0;
}
