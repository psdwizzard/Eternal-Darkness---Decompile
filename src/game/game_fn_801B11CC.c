typedef unsigned int u32;

extern char* __DTKCurrentTrack;
extern void __DTKCallbackForPreparePaused(void);
extern void DVDPrepareStreamAsync(void*, int, u32, void (*)(void));

void __DTKPrepareCurrentTrackPaused(void)
{
    char* entry = __DTKCurrentTrack;
    DVDPrepareStreamAsync(entry + 0x18, 0, *(u32*)(entry + 0x10), __DTKCallbackForPreparePaused);
}
