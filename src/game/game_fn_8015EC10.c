typedef struct Object {
    unsigned char pad0[0x10];
    volatile int current;
    volatile int previous;
    int value;
} Object;

extern void luaK_patchlist(Object*, int, int);

int luaK_getlabel(Object* object)
{
    int current = object->current;
    int previous = object->previous;
    if (current != previous) {
        object->previous = current;
        luaK_patchlist(object, object->value, previous);
        object->value = -1;
    }
    return object->current;
}
