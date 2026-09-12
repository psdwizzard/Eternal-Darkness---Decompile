typedef struct Object80201DE0 Object80201DE0;

struct Object80201DE0 {
    unsigned char padding[0x18];
    void* value;
};

void fn_80201DE0(Object80201DE0* object, void* value)
{
    object->value = value;
}
