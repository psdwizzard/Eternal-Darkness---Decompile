typedef signed short s16;
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

extern void fn_801F5CFC(Slot*, int, Owner*);

s16 fn_801F6054(s16 index, u16 count, Slot* slots, int object_index, Owner* owner)
{
    goto test;
next:
    index++;
    if (index >= count) {
        index = 0;
    }
test:
    if (slots[index].active != 1) {
        goto found;
    }
    if (!(count <= 0)) {
        goto next;
    }
found:

    if (count == 0) {
        index = 0;
    }
    fn_801F5CFC(&slots[index], (u16)object_index, owner);
    return index;
}
