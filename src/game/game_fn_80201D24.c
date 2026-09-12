typedef struct Object80201D24 Object80201D24;

struct Object80201D24 {
    unsigned char padding[0x14];
    int value;
};

void fn_80201D24(Object80201D24 *object, int value)
{
    object->value = value;
}
