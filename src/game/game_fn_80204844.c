typedef struct Object {
    unsigned char pad[8];
    int type;
} Object;

extern Object *fn_80201BC0(Object *object);

Object *fn_80204844(Object *object, int type)
{
    while (object != 0) {
        if (type == object->type) {
            break;
        }
        object = fn_80201BC0(object);
    }
    return object;
}
