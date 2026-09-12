typedef signed short s16;
typedef unsigned int u32;

typedef struct Object80201DF8 Object80201DF8;

struct Object80201DF8 {
    unsigned char padding[0x30];
    s16 value;
};

extern u32 fn_80201CCC(Object80201DF8* object);

s16 fn_80201DF8(Object80201DF8* object, s16 value)
{
    s16 previous;

    if (fn_80201CCC(object) & 0x800) {
        previous = object->value;
    } else {
        previous = object->value;
        object->value = value;
    }

    return previous;
}
