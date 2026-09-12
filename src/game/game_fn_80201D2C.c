typedef struct Object80201D2C Object80201D2C;

struct Object80201D2C {
    unsigned char padding[0x18];
    int value;
};

void fn_80201D2C(Object80201D2C *object, int value)
{
    object->value = value;
}
