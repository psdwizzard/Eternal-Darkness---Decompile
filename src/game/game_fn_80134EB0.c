typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Slot {
    void* owner;
    u32 capacity;
    void* data;
    int field_C;
    int field_10;
    char pad_14[2];
    u8 state;
    u8 pad_17;
} Slot;

extern Slot* lbl_8064CF88;
extern int lbl_8064CFAC;

Slot* fn_80134EB0(u32 required)
{
    int i;
    Slot* slot = lbl_8064CF88;
    Slot* result = 0;
    int count = lbl_8064CFAC;
    i = 0;

    while (result == 0 && i < count) {
        if (slot->owner == 0 && slot->capacity >= required) {
            slot->state = 4;
            result = slot;
        }
        i++;
        slot++;
    }
    return result;
}
