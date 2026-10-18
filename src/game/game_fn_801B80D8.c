typedef unsigned char u8;
typedef unsigned int u32;

extern u8 sndActive;
extern u8* synthVoice;

extern u32 vidGetInternalId(void);
extern void macSetExternalKeyoff(void*);

u32 synthSendKeyOff(void* object)
{
    u8 index;
    u32 found = 0;

    if (sndActive != 0) {
        u32 handle = vidGetInternalId();

        while (handle != -1) {
            index = handle;

            if (handle == *(u32*)(synthVoice + index * 0x404 + 0xF4)) {
                macSetExternalKeyoff(synthVoice + index * 0x404);
                found = 1;
            }
            handle = *(u32*)(synthVoice + index * 0x404 + 0xEC);
        }
    }
    return found;
}
