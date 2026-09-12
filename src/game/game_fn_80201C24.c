typedef struct Object80201C24 Object80201C24;

struct Object80201C24 {
    unsigned char padding[0x2C];
    void *linked;
};

void *fn_80201C24(Object80201C24 *object)
{
    return object->linked;
}
