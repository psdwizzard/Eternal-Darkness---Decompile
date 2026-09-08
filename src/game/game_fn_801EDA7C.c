typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

extern int lbl_8064C378;
extern int lbl_8064C4EC;
extern u8 lbl_8064D5F8;
extern int lbl_8064D624;
extern int lbl_8064D630;
extern int lbl_8064D63C;
extern int lbl_8064D6E8;
extern int lbl_80265D80[];

extern int fn_801ED58C(void);
extern int fn_801EDA74(void);
extern int* fn_8015AB00(int);
extern int fn_801EDF80(s16*, int, int, int, int*, int, int, int, int, void*);
extern void fn_801EDD58(void);
extern void fn_802262B8(u8);
extern void fn_8022A2F4(u8);

int fn_801EDA7C(s16* values, int context, int flags, void* state)
{
    int total;
    int count;
    unsigned int index;
    int active_mask;
    int special;
    int iteration_total;
    int enabled;
    int old_mode;
    int object;
    int parameter;
    int bit;
    int mode;
    int* setup;

    total = 0;
    count = 0;
    old_mode = fn_801ED58C();
    object = fn_801EDA74();
    active_mask = lbl_8064C378;
    special = lbl_8064D6E8;
    setup = fn_8015AB00(2);
    parameter = 30;
    iteration_total = 0;

    if (values != 0) {
        values[3] = -1;
        if (old_mode != 0) {
            values[9] = setup[9];
        } else {
            values[9] = -1;
        }

        if (object != 0) {
            if (lbl_8064D624 & 1) {
                values[3] = 0;
            }
            if (lbl_8064D624 & 0x4000) {
                values[3] = 0;
                flags &= ~0x200;
            } else if (lbl_8064D624 & 2) {
                values[3] = 1;
            } else if (lbl_8064D624 & 0x2000) {
                values[3] = 2;
            } else if (lbl_8064D624 & 0x8000) {
                values[3] = 3;
            }
            flags &= ~0x80;
        }
    }

    lbl_8064D630 = 0;
    if (fn_801EDF80(values, 0, 0, 0, &parameter, 0, 10, context, flags, state) != 0) {
        total = 1;
        count = 1;
    }

    index = 0;
    do {
        int slot = lbl_80265D80[index];
        int candidate;

        if (values != 0) {
            candidate = values[slot];
            if (slot == 1) {
                switch (lbl_8064D5F8) {
                case 0:
                    candidate = values[1];
                    break;
                case 1:
                    candidate = values[6];
                    break;
                case 2:
                    candidate = values[8];
                    break;
                }
            }
        } else {
            if (((u32*)state)[slot] != 0) {
                *(s16*)((u8*)state + 0x5C + slot * 2) = ((u32*)state)[slot];
                candidate = *(s16*)((u8*)state + 0x5C + slot * 2);
            } else {
                *(s16*)((u8*)state + 0x5C + slot * 2) = -1;
                candidate = -1;
            }
        }

        if (candidate != -1) {
            bit = 1 << slot;
            if ((flags & bit) != 0 &&
                ((active_mask & bit) != 0 || special != 0)) {
                mode = index;
                if (slot == 3) {
                    mode = 2;
                }
                enabled = fn_801EDF80(values, total, count, iteration_total,
                                      &parameter, mode, slot, context, flags, state);
                total += enabled;
                count += enabled;
                iteration_total += enabled;
            }
        }
        index++;
    } while (index < 8);

    if (lbl_8064D630 > 8) {
        lbl_8064D630 = 8;
    }
    fn_801EDD58();

    if (values != 0) {
        if (old_mode != 0) {
            values[9] = -1;
        }
        if (object != 0) {
            values[3] = -1;
        }
    }

    if (count != 0 && lbl_8064D63C != count) {
        fn_802262B8((u8)lbl_8064D630);
        fn_8022A2F4((u8)count);
        lbl_8064D63C = count;
        lbl_8064C4EC++;
    }
    return count;
}
