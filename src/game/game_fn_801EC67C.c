typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Source {
    u32 pad0[3];
    int lower;
    int upper;
    int step;
    int initial_delay;
    int delay;
    u32 pad20[2];
    int reverse_count;
    int forward_count;
} Source;

extern u16* lbl_8064D604;
extern int lbl_8064D658;
extern int lbl_8064D65C;
extern int lbl_8064D660;
extern int lbl_8064D664;
extern int lbl_8064D6A0;
extern int lbl_8064D6D8;
extern void DCFlushRange(void*, u32);

void fn_801EC67C(Source* source)
{
    u16* image;
    int value;
    int i;

    if (source == 0)
        return;
    if (lbl_8064D6D8 != 0)
        return;

    if (lbl_8064D658 == 0) {
        for (i = 254; i >= 0; i--)
            lbl_8064D604[i + 1] = lbl_8064D604[i];

        if (lbl_8064D660 == 0) {
            if (lbl_8064D664 == 0) {
                image = lbl_8064D604;
                value = (u8)*image;
                if (value <= source->lower) {
                    lbl_8064D65C = source->step;
                    lbl_8064D664 = source->forward_count;
                } else if (value >= source->upper) {
                    lbl_8064D65C = -source->step;
                    lbl_8064D664 = source->reverse_count;
                }
                *image = (u8)(lbl_8064D65C + *image);
                lbl_8064D6A0 += source->step;
            } else {
                lbl_8064D664--;
            }
            lbl_8064D660 = source->delay;
        }
        lbl_8064D660--;
        lbl_8064D658 = source->initial_delay;
    }

    lbl_8064D658--;
    DCFlushRange(lbl_8064D604, 0x200);
}
