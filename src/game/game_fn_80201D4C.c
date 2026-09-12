typedef struct Object80201D4C Object80201D4C;

struct Object80201D4C {
    unsigned char padding[0x28];
    void* value;
};

void fn_80201D4C(Object80201D4C* object, void* value)
{
    object->value = value;
}
