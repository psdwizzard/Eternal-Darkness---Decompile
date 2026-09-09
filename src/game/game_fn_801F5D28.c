typedef unsigned short u16;

typedef struct Slot {
    u16 active;
    u16 field_2;
    u16 field_4;
    u16 pad;
    void* object;
} Slot;

void fn_801F5D28(Slot* slot)
{
    slot->active = 0;
    slot->field_4 = 0;
    slot->field_2 = 0;
    slot->object = 0;
}
