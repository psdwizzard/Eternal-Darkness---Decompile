typedef unsigned char u8;
typedef signed char s8;
typedef signed int s32;

typedef struct RuntimeSlot {
    u8 data[0x10B];
    s8 active;
    u8 tail[4];
} RuntimeSlot;

typedef struct ObjectState {
    s32 unused;
    RuntimeSlot **installed;
} ObjectState;

extern s32 lbl_8064C548;
extern void *fn_80201B8C();

void fn_80067BAC(void *object)
{
    ObjectState *state = fn_80201B8C(object);
    RuntimeSlot **installed = state != 0 ? state->installed : 0;
    RuntimeSlot *slot = *installed;

    if (slot->active == -1) {
        slot->active = lbl_8064C548;
        lbl_8064C548 = (lbl_8064C548 >= 2) ? 0 : lbl_8064C548 + 1;
    }
}
