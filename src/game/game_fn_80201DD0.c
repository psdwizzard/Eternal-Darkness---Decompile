typedef struct Object80201DD0 Object80201DD0;

struct Object80201DD0 {
    unsigned char padding[0x34];
    void* value;
};

void fn_80201DD0(Object80201DD0* object, void* value)
{
    object->value = value;
}
