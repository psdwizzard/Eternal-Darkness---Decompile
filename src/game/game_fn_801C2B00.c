typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Envelope {
    u8 mode;
    u8 state;
    u8 pad_02[2];
    u32 duration;
    u32 value;
    u32 secondary;
    u32 step;
    u32 attack;
    u32 release;
    u16 level;
    u8 pad_1E[8];
    u8 alternate;
} Envelope;

extern u16 lbl_802529A8[];

int fn_801C2B00(Envelope* envelope)
{
    u32 duration;
    u32 index;
    int done = 0;

    switch (envelope->mode) {
    case 0:
        switch (envelope->state) {
        case 0:
            duration = envelope->attack;
            envelope->duration = duration;
            if (duration != 0) {
                envelope->state = 1;
                envelope->value = 0;
                envelope->step = 0x7FFF0000 / envelope->attack;
                break;
            }
        case 1:
            duration = envelope->release;
            envelope->duration = duration;
            if (duration != 0) {
                envelope->state = 2;
                envelope->value = 0x7FFF0000;
                envelope->step = -(int)((0x7FFF0000 - ((u32)envelope->level << 16)) /
                                         envelope->release);
                break;
            }
        case 2:
            if (envelope->level != 0) {
                envelope->state = 3;
                envelope->value = (u32)envelope->level << 16;
                envelope->step = 0;
                break;
            }
        case 4:
            envelope->value = 0;
            done = 1;
            break;
        }
        break;
    case 1:
        switch (envelope->state) {
        case 0:
            duration = envelope->attack;
            envelope->duration = duration;
            if (duration != 0) {
                envelope->state = 1;
                if (envelope->alternate == 0) {
                    envelope->value = 0;
                    envelope->step = 0x7FFF0000 / envelope->duration;
                } else {
                    envelope->secondary = 0;
                    envelope->value = 0;
                    envelope->step = 0x00C10000 / envelope->duration;
                }
                break;
            }
        case 1:
            envelope->duration = (envelope->release *
                                  ((((u32)193 - envelope->level) << 16) / 193)) >> 16;
            if (envelope->duration != 0) {
                envelope->state = 2;
                envelope->value = 0x7FFF0000;
                envelope->secondary = 0x00C10000;
                envelope->step = -(int)((((u32)193 - envelope->level) << 16) /
                                         envelope->duration);
                break;
            }
        case 2:
            if (envelope->level != 0) {
                envelope->state = 3;
                envelope->secondary = (u32)envelope->level << 16;
                index = envelope->secondary + 0x8000;
                index = 193 - ((int)index >> 16);
                if ((int)index < 0) {
                    index = 0;
                }
                envelope->value = (u32)lbl_802529A8[index] << 16;
                envelope->step = 0;
                break;
            }
        case 4:
            envelope->value = 0;
            done = 1;
            break;
        }
        break;
    }
    return done;
}
