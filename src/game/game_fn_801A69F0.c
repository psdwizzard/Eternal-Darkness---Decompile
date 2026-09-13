typedef unsigned char u8;
typedef signed short s16;

typedef struct InputEntry {
    int bit;
    s16 first;
    s16 pad;
    s16 second;
    u8 tail[2];
    u8 active;
    u8 rest[3];
} InputEntry;

extern InputEntry lbl_80251140[3][4];
extern int lbl_80251200[3];

void fn_801A69F0(int direction)
{
    int group;
    int nonzero = -direction | direction;
    int start = 3;
    int increment = -1;

    nonzero >>= 31;
    start &= ~nonzero;

    if (direction != 0) {
        increment = 1;
    }

    for (group = 0; group < 3; group++) {
        int count = lbl_80251200[group];
        if (count > 0) {
            int index = start;
            s16 position = -30;
            s16 step = 60 / count;
            int done = 0;

            while (!done) {
                InputEntry* entry = &lbl_80251140[group][index];
                if (entry->active != 0) {
                    entry->first = position;
                    position += step;
                    entry->second = position;
                }
                index += increment;
                if (direction != 0) {
                    done = index >= 4;
                } else {
                    done = index < 0;
                }
            }
        }
    }
}
