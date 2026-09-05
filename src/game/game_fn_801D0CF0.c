typedef unsigned char u8;

typedef struct Object Object;
typedef void (*Callback)(Object*, void*);

struct Object {
    char pad0[0x28];
    Callback callback;
    void* callback_arg;
    char pad30[0xFC0];
    u8 flags;
};

void fn_801D0CF0(Object* object)
{
    object->flags |= 1;
    if (object->callback != 0) {
        object->callback(object, object->callback_arg);
    }
}
