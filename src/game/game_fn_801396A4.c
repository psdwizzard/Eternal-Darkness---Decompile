typedef struct Slot {
    int id;
    unsigned char pad04[0x49];
    volatile signed char flag;
    unsigned char pad4E[2];
} Slot;

typedef struct State {
    int current;
    int unused;
    int request;
    int wanted;
    unsigned char pad10[0x2A8];
    Slot slots[2];
} State;

extern State lbl_805AE020;
extern int fn_8013977C(Slot*);

void fn_801396A4(int id)
{
    int other = lbl_805AE020.current ^ 1;

    if (lbl_805AE020.slots[other].id == id) {
        if (lbl_805AE020.slots[lbl_805AE020.current].id != lbl_805AE020.wanted) {
            if (lbl_805AE020.slots[lbl_805AE020.current].flag != 0) {
                fn_8013977C(&lbl_805AE020.slots[lbl_805AE020.current]);
            }
            lbl_805AE020.slots[lbl_805AE020.current].flag = 0;
            *(volatile int*)&lbl_805AE020.current = other;
        }
    } else if (lbl_805AE020.slots[lbl_805AE020.current].id == id &&
               lbl_805AE020.slots[other].id != lbl_805AE020.wanted) {
        if (lbl_805AE020.slots[other].flag != 0) {
            fn_8013977C(&lbl_805AE020.slots[other]);
        }
        lbl_805AE020.slots[other].flag = 0;
    }
}
