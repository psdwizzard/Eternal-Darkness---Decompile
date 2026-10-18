typedef unsigned char u8;

extern int __DTKInterruptFrequency;
extern void* __DTKCurrentTrack;
extern u8 __block_for_ais_isr[];

extern void __DTKCallbackForPlaylist(int);
extern void AISetStreamTrigger(int);
extern void DVDGetStreamPlayAddrAsync(void*, void (*)(int));

void __DTKCallbackForAIInterrupt(int value)
{
    AISetStreamTrigger(value + __DTKInterruptFrequency);
    if (__DTKCurrentTrack != 0) {
        DVDGetStreamPlayAddrAsync(__block_for_ais_isr, __DTKCallbackForPlaylist);
    }
}
