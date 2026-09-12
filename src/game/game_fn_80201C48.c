typedef struct Object80201C48 Object80201C48;

struct Object80201C48 {
    unsigned char padding[0x14];
    void *value;
};

void *fn_80201C48(Object80201C48 *object)
{
    return object->value;
}
