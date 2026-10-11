typedef struct SpellState {
    unsigned int unk0[2];
    unsigned int slots[12];
    unsigned int masks[12];
} SpellState;

extern SpellState lbl_80331748;

static inline void SpellState_Enable(int slot, unsigned int flags)
{
    SpellState* state = &lbl_80331748;
    unsigned int mask = state->masks[slot] | flags;
    unsigned int bits = state->slots[slot] | 0x8000000;

    state->masks[slot] = mask;
    state->slots[slot] = bits;
}

void fn_801119DC(int type, unsigned int flags)
{
    switch (type) {
    case 0x20:
        SpellState_Enable(0, flags);
        break;
    case 0x21:
        SpellState_Enable(1, flags);
        break;
    case 0x22:
        SpellState_Enable(3, flags);
        break;
    case 0x23:
        SpellState_Enable(11, flags);
        break;
    case 0x24:
        SpellState_Enable(6, flags);
        break;
    case 0x25:
        SpellState_Enable(4, flags);
        break;
    case 0x27:
        SpellState_Enable(8, flags);
        break;
    case 0x28:
        SpellState_Enable(5, flags);
        break;
    case 0x29:
        SpellState_Enable(9, flags);
        break;
    case 0x2A:
        SpellState_Enable(7, flags);
        break;
    case 0x2B:
        SpellState_Enable(2, flags);
        break;
    case 0x2C:
        SpellState_Enable(10, flags);
        break;
    }
}
