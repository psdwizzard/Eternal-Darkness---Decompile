typedef struct Object80201E60 Object80201E60;

struct Object80201E60 {
    unsigned char padding[0xC];
    int value;
};

void fn_80201E60(Object80201E60* object, int value)
{
    object->value = value;
}
