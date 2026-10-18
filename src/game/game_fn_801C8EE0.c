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

extern Voice* s3dEmitterRoot;
extern void synthSendKeyOff(u32);

void EmitterShutdown(Voice* voice)
{
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
