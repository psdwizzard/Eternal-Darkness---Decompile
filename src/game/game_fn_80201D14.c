typedef struct Object80201D14 Object80201D14;

struct Object80201D14 {
    unsigned char padding[0x20];
    unsigned char value;
};

void fn_80201D14(Object80201D14 *object, unsigned char value)
{
    object->value = value;
}
