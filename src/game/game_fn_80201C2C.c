typedef struct Object80201C2C Object80201C2C;

struct Object80201C2C {
    unsigned char padding[0x30];
    void *linked;
};

void *fn_80201C2C(Object80201C2C *object)
{
    if (object != 0 && object->linked != 0) {
        return object->linked;
    }
    return 0;
}
