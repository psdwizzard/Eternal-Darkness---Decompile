typedef unsigned int u32;
typedef struct Voice Voice;

struct Voice {
    Voice* previous;
    Voice* next;
    char pad08[8];
    u32 flags;
    char pad14[0x28];
    u32 handle;
};

extern unsigned char sndActive;
extern Voice* s3dEmitterRoot;
extern void synthSendKeyOff(u32);
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

int sndRemoveEmitter(Voice* voice)
{
    if (sndActive != 0) {
        hwDisableIrq();
        if ((voice->flags & 0x10000) != 0) {
            if (voice->previous != 0) {
                voice->previous->next = voice->next;
            }
            if (voice->next != 0) {
                voice->next->previous = voice->previous;
            } else {
                s3dEmitterRoot = voice->previous;
            }
            voice->flags &= 0xFFFF;
            if (voice->handle != 0xFFFFFFFF) {
                synthSendKeyOff(voice->handle);
            }
        }
        hwEnableIrq();
        return 1;
    }
    return 0;
}
