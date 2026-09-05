typedef unsigned char u8;

typedef struct Object {
    char pad_0[0x11C];
    int field_11C;
    int field_120;
} Object;

typedef struct Slot {
    Object* owner;
    int capacity;
    void* data;
    int field_C;
    int field_10;
    char pad_14[4];
} Slot;

extern Slot* lbl_8064CF88;
extern int lbl_8064CF98;
extern int lbl_8064CFAC;

Slot* fn_80134F08(Object* object)
{
    int i;
    Slot* slot = lbl_8064CF88;
    Slot* result = 0;
    int count = lbl_8064CFAC;
    i = 0;

    while (result == 0 && i < count) {
        if (slot->owner == object) {
            if (slot->field_10 == object->field_120 &&
                slot->field_C == object->field_11C) {
                result = slot;
            } else {
                lbl_8064CF98++;
            }
        }
        i++;
        slot++;
    }
    return result;
}
