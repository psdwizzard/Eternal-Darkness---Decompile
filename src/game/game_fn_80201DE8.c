typedef struct Object80201DE8 Object80201DE8;

struct Object80201DE8 {
    unsigned char padding[0x1C];
    void* value;
};

void fn_80201DE8(Object80201DE8* object, void* value)
{
    object->value = value;
}
