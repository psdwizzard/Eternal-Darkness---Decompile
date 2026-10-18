typedef unsigned char u8;
typedef unsigned int u32;

extern u8* synthVoice;

extern void hwGetVirtualSampleID(u8);
extern void vsSampleEndNotify(void);
extern void macSampleEndNotify(void*);
extern void voiceKill(u8);
extern int vsSampleStartNotify(u8);

int synthHWMessageHandler(int command, u32 handle)
{
    u32 offset;
    int result = 0;

    switch (command) {
    case 0:
        offset = (u8)handle * 0x404;
        if (synthVoice[offset + 0x11C] == 0) {
            hwGetVirtualSampleID(handle);
            vsSampleEndNotify();
            if (handle == *(u32*)(synthVoice + offset + 0xF4)) {
                macSampleEndNotify(synthVoice + offset);
            }
        }
        break;
    case 1:
        voiceKill(handle);
        break;
    case 2:
        result = vsSampleStartNotify(handle);
        break;
    case 3:
        hwGetVirtualSampleID(handle);
        vsSampleEndNotify();
        break;
    }
    return result;
}
