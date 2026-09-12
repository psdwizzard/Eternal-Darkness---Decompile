typedef struct Object80201D1C Object80201D1C;

struct Object80201D1C {
    unsigned char padding[0x21];
    unsigned char value;
};

void fn_80201D1C(Object80201D1C *object, unsigned char value)
{
    object->value = value;
}
