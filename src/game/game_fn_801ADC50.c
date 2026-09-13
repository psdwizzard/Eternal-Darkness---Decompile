typedef struct Entry {
    unsigned char prefix[80];
    unsigned int handle;
    unsigned char padding[8];
    unsigned int first;
    unsigned char padding2[4];
    unsigned int second;
    unsigned char remainder[28];
} Entry;

typedef struct State {
    Entry entries[3];
    unsigned int initialized;
    unsigned int interrupts;
    unsigned int interrupt_depth;
} State;

extern State lbl_8060B430;
extern int lbl_8064D308;
extern void fn_801AE530(void);
extern unsigned int fn_801BA2A4(unsigned int, unsigned int, unsigned int,
                               unsigned int, unsigned int, unsigned int,
                               unsigned int, unsigned int, unsigned int,
                               unsigned int, unsigned int,
                               void (*)(void), void*, unsigned int);

void fn_801ADC50(void)
{
    Entry* entry;
    unsigned int index;
    unsigned int zero;

    if (lbl_8064D308 == 0) {
        index = 0;
        entry = &lbl_8060B430.entries[index];
        zero = 0;
        do {
            entry->handle = fn_801BA2A4(0xFF, entry->first, entry->second,
                                        0x7D00, 0, 0x40, 0, 0, zero, zero,
                                        0x30001, fn_801AE530, entry, zero);
            entry++;
            index++;
        } while (index < 3);
        lbl_8064D308 = 1;
    }
}
