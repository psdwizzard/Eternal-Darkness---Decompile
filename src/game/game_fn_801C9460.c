typedef unsigned int u32;
typedef unsigned short u16;
typedef struct Voice Voice;

struct Voice {
    Voice* previous;
    Voice* next;
    char pad08[8];
    u32 flags;
    char pad14[0x30];
    u16 sound_id;
};

typedef struct SoundEntry {
    u16 sound_id;
    char pad02[8];
} SoundEntry;

extern unsigned char sndActive;
extern Voice* s3dEmitterRoot;
extern void EmitterShutdown(Voice*);
extern void hwDisableIrq(void);
extern void hwEnableIrq(void);

void s3dKillEmitterByFXID(SoundEntry* entries, u32 count)
{
    Voice* voice = s3dEmitterRoot;
    while (voice != 0) {
        u32 i;
        Voice* previous = voice->previous;
        SoundEntry* entry = entries;
        for (i = 0; i < count; i++, entry++) {
            if (voice->sound_id == entry->sound_id) {
                if (sndActive != 0) {
                    hwDisableIrq();
                    if ((voice->flags & 0x10000) != 0) {
                        EmitterShutdown(voice);
                    }
                    hwEnableIrq();
                }
                break;
            }
        }
        voice = previous;
    }
}
