typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StreamState {
    u8 pad_000[0x124];
    u32 previous;
    u32 current;
    u16 step;
    s8 percent;
} StreamState;

extern u16 lbl_80252160[];

void DoSetPitch(StreamState* state)
{
    u32 currentValue = state->current & 0xFFFFFF;
    u16* table = lbl_80252160;
    u32 previousValue = state->previous & 0xFFFFFF;
    u32 ratio;
    u32 value;
    u32 octave;
    u32 one;
    int index;
    int step;

    if (previousValue == currentValue) {
        state->step = state->previous >> 24;
        state->percent = 0;
        return;
    }

    if (previousValue < currentValue) {
        ratio = (currentValue << 12) / previousValue;
        value = ratio >> 12;
        octave = 0;
        one = 1;
        for (index = 0; index < 11; index++) {
            if (value < (one << (octave + 1))) {
                break;
            }
            octave++;
        }
        value = ratio / (1 << octave);
        index = 11;
        do {
            if (value > table[index]) {
                break;
            }
            index--;
        } while (1);
        state->step = (state->previous >> 24) + octave * 12 + index;
        state->percent = (value - table[index]) * 100 / (table[index + 1] - table[index]);
    } else {
        ratio = (previousValue << 12) / currentValue;
        value = ratio >> 12;
        octave = 0;
        one = 1;
        for (index = 0; index < 11; index++) {
            if (value < (one << (octave + 1))) {
                break;
            }
            octave++;
        }
        ratio = ratio / (1 << octave);
        index = 11;
        do {
            if (ratio > table[index]) {
                break;
            }
            index--;
        } while (1);
        step = octave * 12 + index;
        if (step > (int)(state->previous >> 24)) {
            state->percent = 0;
            state->step = 0;
            return;
        }
        state->step = (state->previous >> 24) - step;
        state->percent = (table[index] - ratio) * 100 / (table[index + 1] - table[index]);
    }
}
