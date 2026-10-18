typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Voice {
    char pad00[0x10];
    u32 flags;
} Voice;

extern u8 sndActive;

int sndCheckEmitter(Voice* voice)
{
    if (sndActive != 0) {
        return (voice->flags & 0x10000) != 0;
    }
    return 0;
}
