typedef unsigned int u32;

typedef struct EXIControl {
    void *callback;
    char pad_04[8];
    u32 state;
    char pad_10[0x30];
} EXIControl;

extern EXIControl Ecb_80640AA8[3];

extern void __OSMaskInterrupts(u32);
extern void __OSUnmaskInterrupts(u32);
extern void *fn_8020C9D8(int);

void fn_80206778(int chan, EXIControl *exi)
{
    EXIControl *exi2 = &Ecb_80640AA8[2];

    switch (chan) {
    case 0:
        if ((exi->callback == 0 && exi2->callback == 0) ||
            (exi->state & 0x10)) {
            __OSMaskInterrupts(0x00410000);
        } else {
            __OSUnmaskInterrupts(0x00410000);
        }
        break;
    case 1:
        if (exi->callback == 0 || (exi->state & 0x10)) {
            __OSMaskInterrupts(0x00080000);
        } else {
            __OSUnmaskInterrupts(0x00080000);
        }
        break;
    case 2:
        if (fn_8020C9D8(0x19) == 0 || (exi->state & 0x10)) {
            __OSMaskInterrupts(0x40);
        } else {
            __OSUnmaskInterrupts(0x40);
        }
        break;
    }
}
