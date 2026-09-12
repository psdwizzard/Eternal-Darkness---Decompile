typedef struct Object80201C84 Object80201C84;

struct Object80201C84 {
    unsigned char padding[0x20];
    void *value;
};

void *fn_80201C84(Object80201C84 *object)
{
    return object->value;
}
