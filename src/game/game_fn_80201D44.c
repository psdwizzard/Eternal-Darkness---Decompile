typedef struct Object80201D44 Object80201D44;

struct Object80201D44 {
    unsigned char padding[8];
    int value;
};

void fn_80201D44(Object80201D44 *object, int value)
{
    object->value = value;
}
