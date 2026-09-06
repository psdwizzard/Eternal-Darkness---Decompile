typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct Envelope {
    u8 mode;
    u8 state;
    u8 pad_02[2];
    u32 duration;
    u32 value;
    s32 secondary;
    s32 step;
    u8 pad_14[0x12];
    u8 alternate;
} Envelope;

extern u16 lbl_802529A8[];
extern int fn_801C2B00(Envelope* envelope);

int fn_801C2F34(Envelope* envelope, u16* level, u16* delta)
{
    int done = 0;
    s32 previous;
    s32 change;

    switch (envelope->mode) {
    case 0:
        if (envelope->state != 3) {
            previous = envelope->value;
            envelope->value += envelope->step;
            *level = previous >> 16;
            if (envelope->step >= 0) {
                *delta = envelope->step >> 21;
            } else {
                *delta = -((-envelope->step) >> 21);
            }
            if (--envelope->duration == 0) {
                done = fn_801C2B00(envelope);
            }
        } else {
            *level = (s32)envelope->value >> 16;
            *delta = 0;
        }
        break;
    case 1:
        if (envelope->state != 3) {
            previous = envelope->value;
            if (envelope->alternate == 0 && envelope->state == 1) {
                envelope->value += envelope->step;
            } else {
                envelope->secondary += envelope->step;
                change = envelope->secondary + 0x8000;
                change = 193 - (change >> 16);
                if (change < 0) {
                    change = 0;
                }
                envelope->value = (u32)lbl_802529A8[change] << 16;
            }
            *level = previous >> 16;
            change = envelope->value - previous;
            if (change >= 0) {
                *delta = change >> 21;
            } else {
                *delta = -((-change) >> 21);
            }
            if (--envelope->duration == 0) {
                done = fn_801C2B00(envelope);
            }
        } else {
            *level = (s32)envelope->value >> 16;
            *delta = 0;
        }
        break;
    }
    return done;
}
