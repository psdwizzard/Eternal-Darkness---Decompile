typedef unsigned char u8;

typedef struct Entry {
    u8 pad000[0x17A];
    u8 active;
    u8 pad17B[9];
} Entry;

extern Entry lbl_8060B5E0[];
extern void fn_801B01F8(Entry*, int, int);
extern void VIWaitForRetrace(void);
extern void fn_801A99B4(void);
extern void fn_801E81C8(void);
extern void fn_801B0E6C(void);
extern void fn_801B0E68(int);
extern void fn_801AEE64(void);

void fn_801B0D30(void)
{
    int i;
    int active;
    int frames = 0;
    Entry* entry;

    do {
        entry = lbl_8060B5E0;
        active = 0;
        for (i = 0; i < 4; i++, entry++) {
            if (entry->active != 0) {
                fn_801B01F8(entry, 0, 7);
                active++;
            }
        }
        if (active != 0) {
            VIWaitForRetrace();
            fn_801A99B4();
            fn_801E81C8();
            fn_801B0E6C();
            frames++;
            if (frames > 60) {
                fn_801B0E68(7);
            }
        }
    } while (active != 0);
    fn_801AEE64();
}
