typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Entry {
    u8 state;
    u8 padding01[3];
    u32 id;
    u8 padding08[124];
} Entry;

extern Entry lbl_8060B430[];
extern void fn_801ADC08(void);
extern void fn_801ADBC0(void);
extern void fn_801AE1D0(u32, int);
extern void fn_801AEF18(int);
extern void fn_801E81C8(void);
extern void VIWaitForRetrace(void);
extern void fn_801B0E68(int);

void fn_801AEE64(void)
{
    int retries;
    int i;
    int active;
    int stop;
    Entry* entry;

    retries = 0;
    stop = 0;

    do {
        entry = lbl_8060B430;
        active = 0;
        fn_801ADC08();
        for (i = 0; i < 3; i++, entry++) {
            if (entry->state != 0) {
                fn_801AEF18(99);
                fn_801AE1D0(entry->id, stop);
                active++;
            }
        }
        fn_801ADBC0();
        if (active != 0) {
            VIWaitForRetrace();
            fn_801E81C8();
            retries++;
            if (retries > 3) {
                stop = 1;
            }
        }
    } while (active != 0);

    if (retries != 0) {
        fn_801B0E68(100);
    }
}
