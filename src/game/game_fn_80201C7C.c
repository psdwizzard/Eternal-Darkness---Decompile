typedef struct Object80201C7C Object80201C7C;

struct Object80201C7C {
    unsigned char padding[0x1C];
    void *value;
};

void *fn_80201C7C(Object80201C7C *object)
{
    return object->value;
}
