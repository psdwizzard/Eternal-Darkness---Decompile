typedef unsigned char u8;
typedef short s16;
typedef int s32;
#define NULL 0

typedef struct Counts {
    u8 pad[0xEA];
    s16 counts[1];
} Counts;

typedef struct Holder {
    u8 pad0[0x8C];
    Counts *counts;
    u8 pad90[0x94 - 0x90];
    s32 mode;
    u8 pad98[0x9F - 0x98];
    u8 kind;
} Holder;

extern Holder *fn_80201B8C(void *object);
extern int fn_80066D04(void *object, int slot);
extern void fn_801A7678(void *target, int slot);

void fn_800BED54(void *object, void *target, s32 *slot) {
    Holder *holder;
    Counts *counts;

    holder = fn_80201B8C(object);
    if (holder != NULL) {
        if (holder->kind == 4) {
            if (*slot == 0 || *slot == 8 || *slot == 9) {
                if (fn_80066D04(object, 0) != 0) {
                    *slot = 0;
                } else if (fn_80066D04(object, 8) != 0) {
                    *slot = 8;
                } else if (fn_80066D04(object, 9) != 0) {
                    *slot = 9;
                } else if (fn_80066D04(object, 1) != 0) {
                    *slot = 1;
                } else {
                    *slot = -1;
                }
                fn_801A7678(target, *slot);
            } else if (*slot == -1) {
                if (fn_80066D04(object, 1) != 0) {
                    *slot = 1;
                    fn_801A7678(target, *slot);
                }
            }
        } else if (holder->kind == 5) {
            if (holder->mode == 3 && *slot == 0) {
                *slot = 1;
                fn_801A7678(target, *slot);
            }
        } else if (holder->kind == 13) {
            counts = holder->counts;
            if ((*slot != -1 && fn_80066D04(object, *slot) == 0) || counts->counts[*slot] == 0) {
                switch (holder->mode) {
                case 1:
                    if (*slot == 1) {
                        *slot = 12;
                    } else {
                        *slot = -1;
                    }
                    break;
                case 2:
                    if (*slot == 1) {
                        if (fn_80066D04(object, 0) != 0 && counts->counts[0] > 0) {
                            *slot = 0;
                        } else if (fn_80066D04(object, 14) != 0 && counts->counts[14] > 0) {
                            *slot = 14;
                        }
                    } else {
                        *slot = -1;
                    }
                    break;
                case 3:
                    if (*slot == 1) {
                        *slot = 12;
                    } else {
                        *slot = -1;
                    }
                    break;
                }
                fn_801A7678(target, *slot);
            }
        } else if (*slot == -1) {
            if (fn_80066D04(object, 1) != 0) {
                *slot = 1;
                fn_801A7678(target, *slot);
            }
        }
    }
    if (*slot != -1 && fn_80066D04(object, *slot) == 0) {
        if (fn_80066D04(object, 1) != 0) {
            *slot = 1;
            fn_801A7678(target, *slot);
        }
    }
}
