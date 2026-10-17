typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef unsigned int u32;
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

typedef struct {
    u8 pad[0xA4];
    u32 value;
} Data;

extern void *fn_80201B8C(unsigned char *object);
extern s32 fn_80066D04(s32 context, s32 slot);
extern void fn_801A7678(Data *target, u32 slot);

void fn_800BED54(s32 context, void *target, s32 *slot) {
    Holder *holder;
    Counts *counts;

    holder = (Holder *)fn_80201B8C((u8 *)context);
    if (holder != NULL) {
        if (holder->kind == 4) {
            if (*slot == 0 || *slot == 8 || *slot == 9) {
                if (fn_80066D04(context, 0) != 0) {
                    *slot = 0;
                } else if (fn_80066D04(context, 8) != 0) {
                    *slot = 8;
                } else if (fn_80066D04(context, 9) != 0) {
                    *slot = 9;
                } else if (fn_80066D04(context, 1) != 0) {
                    *slot = 1;
                } else {
                    *slot = -1;
                }
                fn_801A7678(target, *slot);
            } else if (*slot == -1) {
                if (fn_80066D04(context, 1) != 0) {
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
            if ((*slot != -1 && fn_80066D04(context, *slot) == 0) || counts->counts[*slot] == 0) {
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
                        if (fn_80066D04(context, 0) != 0 && counts->counts[0] > 0) {
                            *slot = 0;
                        } else if (fn_80066D04(context, 14) != 0 && counts->counts[14] > 0) {
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
            if (fn_80066D04(context, 1) != 0) {
                *slot = 1;
                fn_801A7678(target, *slot);
            }
        }
    }
    if (*slot != -1 && fn_80066D04(context, *slot) == 0) {
        if (fn_80066D04(context, 1) != 0) {
            *slot = 1;
            fn_801A7678(target, *slot);
        }
    }
}
