typedef struct Object80201C50 Object80201C50;

struct Object80201C50 {
    unsigned char padding[0x18];
    void *value;
};

void *fn_80201C50(Object80201C50 *object)
{
    return object->value;
}
