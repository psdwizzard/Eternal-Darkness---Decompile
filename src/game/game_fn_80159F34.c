typedef struct Slot {
    short id;
    short state;
    char pad[8];
    int counter;
    char tail[8];
} Slot;

extern volatile Slot lbl_805B6F80[];
extern int lbl_8064D17C;

extern void* memset(void*, int, unsigned int);
extern int fn_80158E88(short);
extern void fn_80159E0C(void);
extern int fn_80159EEC(void);

void fn_80159F34(short current, int count, short* ids)
{
    int occupied[4];
    int present[4];
    int i;
    int j;
    volatile Slot* slot;
    int remaining;

    memset(occupied, 0, sizeof(occupied));
    memset(present, 0, sizeof(present));

    i = fn_80158E88(current);
    if (i != -1) {
        occupied[i] = 1;
    }

    fn_80159E0C();

    for (i = 0; i < count; i++) {
        for (j = 0; j < lbl_8064D17C; j++) {
            if (ids[i] == lbl_805B6F80[j].id && ids[i] != -1) {
                present[i] = 1;
                occupied[j] = 1;
                lbl_805B6F80[j].counter = 0;
            }
        }
    }

    for (i = 0; i < count; i++) {
        if (present[i] != 1) {
            j = fn_80158E88(ids[i]);
            if (j == -1) {
                j = fn_80159EEC();
                occupied[j] = 2;
                lbl_805B6F80[j].id = ids[i];
                lbl_805B6F80[j].state = 0;
            }
            lbl_805B6F80[j].counter = 0;
        }
    }

    for (slot = lbl_805B6F80, remaining = lbl_8064D17C; remaining > 0;
         remaining--, slot++) {
        slot->counter;
    }
}
