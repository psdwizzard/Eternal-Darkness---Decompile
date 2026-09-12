typedef struct Object80201D3C Object80201D3C;

struct Object80201D3C {
    unsigned char padding[0x38];
    int value;
};

void fn_80201D3C(Object80201D3C *object, int value)
{
    object->value = value;
}
