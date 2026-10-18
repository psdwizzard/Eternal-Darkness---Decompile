typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Envelope {
    u8 mode;
    u8 state;
    u8 pad_02[2];
    u32 duration;
    u32 value;
    u32 secondary;
    u32 step;
    u8 pad_14[0x12];
    u8 alternate;
} Envelope;

extern u8 dspScale2IndexTab[];
extern float lbl_80650F78;
extern u32 fn_800F5C54(double value);

int adsrStartRelease(Envelope* envelope, u32 duration)
{
    float scaled;

    switch (envelope->mode) {
    case 0:
        envelope->state = 4;
        envelope->duration = duration;
        if (duration == 0) {
            envelope->duration = 1;
            envelope->step = 0;
            return 1;
        }
        envelope->step = -(int)(envelope->value / duration);
        break;
    case 1:
        if (envelope->alternate == 0 && envelope->state == 1) {
            envelope->secondary =
                (u32)(193 - dspScale2IndexTab[(int)envelope->value >> 21]) << 16;
        }
        scaled = lbl_80650F78 * (int)envelope->secondary;
        envelope->duration = fn_800F5C54(scaled * duration) >> 12;
        envelope->state = 4;
        if (envelope->duration == 0) {
            envelope->duration = 1;
            envelope->value = 0;
            envelope->secondary = 0;
            envelope->step = 0;
            return 1;
        }
        envelope->step = -(int)(envelope->secondary / envelope->duration);
        break;
    }
    return 0;
}
