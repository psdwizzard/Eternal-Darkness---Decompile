typedef unsigned char u8;

typedef struct VoiceUpdate {
    u8 pad[0x28];
    void* voice;
    u8 type;
} VoiceUpdate;

extern void seqStop(void*);
extern void seqPause(void*);
extern void seqMute(void*, int, int);

void HandleFaderTermination(VoiceUpdate* update)
{
    switch (update->type) {
    case 1:
        seqStop(update->voice);
        break;
    case 2:
        seqPause(update->voice);
        break;
    case 3:
        seqMute(update->voice, 0, 0);
        break;
    }
}
