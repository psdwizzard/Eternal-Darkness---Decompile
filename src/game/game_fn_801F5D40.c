typedef unsigned short u16;

typedef struct Slot {
    u16 active;
    u16 field_2;
    u16 field_4;
    u16 pad;
    void* object;
} Slot;

extern void fn_801F5DAC(Slot*);

#pragma use_lmw_stmw on

void fn_801F5D40(Slot* slot, u16 count)
{
    u16 i = 0;

    for (; i < count; i++, slot++) {
        if (slot->active != 0) {
            fn_801F5DAC(slot);
        }
    }
}
