typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Source {
    u32 pad0[3];
    int lower;
    int upper;
    int step;
    u32 pad18;
    int delay;
    u32 pad20[2];
    int reverse_count;
    int forward_count;
} Source;

extern u16* lbl_8064D604;
extern int lbl_8064D65C;
extern int lbl_8064D660;
extern int lbl_8064D664;
extern int lbl_8064D6A0;

void fn_801EBDDC(Source* source)
{
    int index;
    int value;

    if (lbl_8064D604 == 0)
        return;
    if (source == 0)
        return;

    lbl_8064D65C = source->step;
    lbl_8064D664 = source->forward_count;
    *lbl_8064D604 = source->lower;
    lbl_8064D6A0 = 0;

    for (index = 254; index >= 0; index--) {
        if (lbl_8064D660 == 0) {
            if (lbl_8064D664 == 0) {
                value = *lbl_8064D604;

                if ((u8)value <= source->lower) {
                    lbl_8064D65C = source->step;
                    lbl_8064D664 = source->forward_count;
                } else if ((u8)value >= source->upper) {
                    lbl_8064D65C = -source->step;
                    lbl_8064D664 = source->reverse_count;
                }

                *lbl_8064D604 = (u8)(lbl_8064D65C + *lbl_8064D604);
                lbl_8064D6A0 += source->step;
            } else {
                lbl_8064D664--;
            }
            lbl_8064D660 = source->delay;
        }
        lbl_8064D660--;
        lbl_8064D604[index] = *lbl_8064D604;
    }
}
