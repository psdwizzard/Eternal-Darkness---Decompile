typedef signed short s16;

typedef struct Object80201D88 Object80201D88;

struct Object80201D88 {
    unsigned char padding[0x24];
    void *value;
};

extern void fn_80201DF8(void *object, s16 value);

int fn_80201D88(Object80201D88 *object, s16 value)
{
    int result = 0;

    if (object != 0 && object->value != 0) {
        fn_80201DF8(object->value, value);
        result = 1;
    }

    return result;
}
