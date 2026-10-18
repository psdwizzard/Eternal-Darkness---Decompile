typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Envelope {
    u8 mode;
    u8 pad_01[0x1F];
    u32 release;
} Envelope;

extern int adsrStartRelease(Envelope* envelope, u32 duration);

int adsrRelease(Envelope* envelope)
{
    switch (envelope->mode) {
    case 0:
    case 1:
        return adsrStartRelease(envelope, envelope->release);
    }
    return 0;
}
