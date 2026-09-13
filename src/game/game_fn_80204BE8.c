typedef struct Object80204BE8 Object80204BE8;

struct Object80204BE8 {
    unsigned char pad_00[0x2C];
    void *value;
};

extern void *fn_80157760(int primary_index, int secondary_index);

void *fn_80204BE8(Object80204BE8 *object, int secondary_index, int primary_index)
{
    if (object != 0) {
        object->value = fn_80157760(primary_index, secondary_index);
        return object->value;
    }

    return 0;
}
