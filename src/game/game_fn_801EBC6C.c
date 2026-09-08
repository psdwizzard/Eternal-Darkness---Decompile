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

typedef struct State {
    int count;
    int delay;
    int step;
    u32 padC;
    int accumulator;
    u16* image;
} State;

extern int lbl_8064D6A0;
extern void* memset(void*, int, u32);

void fn_801EBC6C(Source* source, State* state, u16* image)
{
    register State* work = state;
    register Source* input = source;
    register u16* output = image;
    int value;
    int i;

    memset(work, 0, 0x18);
    work->image = output;
    work->step = input->step;
    work->count = input->forward_count;

    if (output != 0 && input != 0) {
        value = (input->lower + work->step) & 0xFFFF;
        lbl_8064D6A0 = 0;

        for (i = 0x1FE; i >= 0; i -= 2) {
            if (work->delay == 0) {
                if (work->count == 0) {
                    int step;
                    if (value <= input->lower) {
                        work->step = input->step;
                        work->count = input->forward_count;
                    } else if (value >= input->upper) {
                        work->step = -input->step;
                        work->count = input->reverse_count;
                    }

                    step = work->step;
                    if (input->upper == input->lower && (unsigned char)value == input->lower)
                        step = 0;

                    step += value;
                    work->accumulator += input->step;
                    value = ((u16)(0xFF - (unsigned char)step) << 8) | (unsigned char)step;
                } else {
                    work->count--;
                }
                work->delay = input->delay;
            }
            work->delay--;
            *(u16*)((char*)work->image + i) = value;
        }
    }
}
