typedef struct Object {
    unsigned char pad0[0x10];
    volatile int current;
    volatile int previous;
    int value;
} Object;

extern void fn_8015F1F8(Object*, int, int);

int fn_8015EC10(Object* object)
{
    int current = object->current;
    int previous = object->previous;
    if (current != previous) {
        object->previous = current;
        fn_8015F1F8(object, object->value, previous);
        object->value = -1;
    }
    return object->current;
}
