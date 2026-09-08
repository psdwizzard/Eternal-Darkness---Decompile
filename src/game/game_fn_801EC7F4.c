typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Source {
    u32 pad0[3];
    int lower;
    int upper;
    int step;
    int count;
    int delay;
    u32 pad20[2];
    int reverse_count;
    int forward_count;
} Source;

typedef struct Destination {
    int pause;
    int delay;
    int step;
    u32 padC;
    int accumulator;
    u16* image;
} Destination;

extern int lbl_8064D6D8;
extern void DCFlushRange(void*, u32);

void fn_801EC7F4(Source* source, Destination* destination)
{
    int channel;
    int i;
    int value;
    int pixel;

    if (source == 0)
        return;
    if (lbl_8064D6D8 != 0)
        return;

    for (channel = 0; channel < source->count; channel++) {
        for (i = 254; i >= 0; i--)
            destination->image[i + 1] = destination->image[i];

        if (destination->delay == 0) {
            if (destination->pause == 0) {
                pixel = (u8)*destination->image;
                value = destination->step + pixel;
                value = source->upper < (value > source->lower ? value : source->lower)
                            ? source->upper
                            : (value > source->lower ? value : source->lower);
                *destination->image = (u16)(((255 - value) << 8) | value);

                value = (u8)*destination->image;
                if (value <= source->lower) {
                    destination->step = source->step;
                    destination->pause = source->forward_count;
                } else if (value >= source->upper) {
                    destination->step = -source->step;
                    destination->pause = source->reverse_count;
                }
                destination->accumulator += source->step;
            } else {
                destination->pause--;
            }
            destination->delay = source->delay;
        }
        destination->delay--;
    }
    DCFlushRange(destination->image, 0x200);
}
