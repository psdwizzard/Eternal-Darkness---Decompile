typedef struct Slot {
    int state;
    int object;
    int pad08;
    int stamp;
    int active;
    volatile unsigned char flags;
    unsigned char tail[3];
} Slot;

extern unsigned char lbl_805E2B1C[];
extern unsigned char lbl_805E2B7C[];
extern Slot lbl_80320DF0[];
extern int lbl_8064B708;

extern int fn_8020D318(void *, void *, int);
extern int fn_8020D3F4(void *, int, int);
extern void fn_800BD0F0(int, int);

void fn_800BDE24(void)
{
    Slot *slot;
    int i;

    while (fn_8020D318(lbl_805E2B7C, 0, 0) != 0) {
    }
    fn_8020D3F4(lbl_805E2B1C, -0x6B5, 1);
    fn_8020D318(lbl_805E2B7C, 0, 1);

    for (i = 0; i < 20; i++) {
        slot = &lbl_80320DF0[i];
        if ((slot->flags & 1) != 0 && (slot->flags & 0xE) != 0 && lbl_8064B708 != 0) {
            fn_800BD0F0(i, slot->object);
        }
    }
}
