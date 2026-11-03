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

extern ObjectState *fn_80201B8C(int);
extern SlotState lbl_80320DF0[];
extern SelectionTable lbl_80320FD0[];

void fn_800BCD2C(int object_id)
{
    ObjectState *object = fn_80201B8C(object_id);
    SelectionState *state = object->selection;
    void *wanted;
    int side = lbl_80320DF0[state->slot].side;
    SelectionTable *table = &lbl_80320FD0[state->group];
    int other_side = side ^ 1;
    wanted = lbl_80320FD0[state->group].entries[other_side]
        [lbl_80320FD0[state->group].selected[other_side]];

    if (wanted != 0) {
        int i = 1;
        void **entry = &table->entries[side][1];

        while (*entry != 0 && i < 100) {
            if (wanted == *entry) {
                lbl_80320FD0[state->group].selected[side] = i;
                return;
            }
            entry++;
            i++;
        }
    }
    lbl_80320FD0[state->group].selected[side] = 0;
}
