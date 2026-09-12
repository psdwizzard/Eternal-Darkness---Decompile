typedef struct Object80201DC8 Object80201DC8;

struct Object80201DC8 {
    unsigned char padding[0x24];
    void* value;
};

void fn_80201DC8(Object80201DC8* object, void* value)
{
    object->value = value;
}
