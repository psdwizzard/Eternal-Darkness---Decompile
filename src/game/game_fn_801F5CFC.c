typedef unsigned short u16;

typedef struct Slot {
    u16 active;
    u16 field_2;
    u16 field_4;
    u16 pad;
    void* object;
} Slot;

typedef struct Owner {
    void* pad;
    char* objects;
} Owner;

void fn_801F5CFC(Slot* slot, u16 index, Owner* owner)
{
    slot->active = 1;
    slot->field_4 = 0;
    slot->field_2 = 0;
    slot->object = owner->objects + index * 0x110;
}
