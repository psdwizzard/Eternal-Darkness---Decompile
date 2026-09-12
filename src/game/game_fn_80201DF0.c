typedef struct Object80201DF0 Object80201DF0;

struct Object80201DF0 {
    unsigned char padding[0x20];
    void* value;
};

void fn_80201DF0(Object80201DF0* object, void* value)
{
    object->value = value;
}
