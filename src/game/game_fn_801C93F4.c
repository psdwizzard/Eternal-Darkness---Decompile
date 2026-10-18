typedef unsigned int u32;
typedef struct Voice Voice;

struct Voice {
    Voice* previous;
    Voice* next;
    char pad08[8];
    u32 flags;
};

extern unsigned char sndActive;
extern Voice* s3dEmitterRoot;
extern void EmitterShutdown(Voice*);
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

void s3dKillAllEmitter(void)
{
    Voice* voice = s3dEmitterRoot;
    while (voice != 0) {
        Voice* previous = voice->previous;
        if (sndActive != 0) {
            hwDisableIrq();
            if ((voice->flags & 0x10000) != 0) {
                EmitterShutdown(voice);
            }
            hwEnableIrq();
        }
        voice = previous;
    }
}
