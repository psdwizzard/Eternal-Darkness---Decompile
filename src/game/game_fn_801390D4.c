typedef struct Slot {
    int resource_id;
    unsigned char pad04[0x3C];
    unsigned char* source;
    void* resource;
    unsigned int size;
    unsigned char state;
    unsigned char flag;
    unsigned char pad4E[2];
} Slot;

typedef struct State {
    unsigned char pad[0x2B8];
    Slot slots[2];
} State;

extern State lbl_805AE020;
extern void fn_80138FE4(int, unsigned int);
extern void DVDClose(void*);
extern void fn_80139940(int);

void fn_801390D4(int offset, void* pointer)
{
    int index = pointer != &lbl_805AE020.slots[0].pad04[0];

    if (offset == -1) {
        lbl_805AE020.slots[index].state = 3;
    } else {
        fn_80138FE4(index, (unsigned int)(lbl_805AE020.slots[index].source + offset));
    }
    DVDClose(pointer);
    fn_80139940(0);
}
