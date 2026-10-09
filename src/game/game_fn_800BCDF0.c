typedef struct ObjectState {
    unsigned char pad00[0x8C];
    struct SelectionState *selection;
} ObjectState;

typedef struct SelectionState {
    unsigned char pad00[0xAC];
    int group;
    int slot;
} SelectionState;

typedef struct SelectionTable {
    void *entries[2][100];
    int selected[2];
    unsigned char pad328[0x10];
} SelectionTable;

typedef struct SlotState {
    int side;
    unsigned char pad04[0x14];
} SlotState;

extern int fn_80201B54();
extern ObjectState *fn_80201B8C();
extern SlotState lbl_80320DF0[];
extern SelectionTable lbl_80320FD0[];

int fn_800BCDF0(void *object)
{
    int result = -1;
    SelectionState *state;
    int side;

    fn_80201B54(object);
    state = fn_80201B8C(object)->selection;
    if (state->slot != -1) {
        if (state->group != 1) {
            side = lbl_80320DF0[state->slot].side;
            if (side == 0 || side == 1) {
                result = lbl_80320FD0[state->group].selected[side];
                lbl_80320FD0[state->group].selected[side] = 0;
            }
        }
    }

    return result;
}
