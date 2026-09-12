typedef struct Object80201DD8 Object80201DD8;

struct Object80201DD8 {
    unsigned char padding[0x14];
    void* value;
};

void fn_80201DD8(Object80201DD8* object, void* value)
{
    object->value = value;
}
