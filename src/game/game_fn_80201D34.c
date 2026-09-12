typedef struct Object80201D34 Object80201D34;

struct Object80201D34 {
    unsigned char padding[0xC];
    int value;
};

void fn_80201D34(Object80201D34 *object, int value)
{
    object->value = value;
}
