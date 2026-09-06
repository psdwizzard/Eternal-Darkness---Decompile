typedef unsigned char u8;

typedef struct Object800A3C4C Object800A3C4C;
typedef void (*Callback800A3C4C)(Object800A3C4C*, void*, int, int);
typedef struct Vtable800A3C4C {
    u8 pad0[0x28];
    Callback800A3C4C callback;
} Vtable800A3C4C;

struct Object800A3C4C {
    Vtable800A3C4C* vtable;
};

typedef struct Wrapper800A3C4C {
    u8 pad0[0x64];
    Object800A3C4C* object;
} Wrapper800A3C4C;

/*
 * Behavior-complete, size-exact reconstruction. Retail reserves r8/r7 for the
 * nested object and vtable while this split TU selects r6/r5.
 * Objdiff: 98.21429%, 56/56 bytes, with no relocations on either side.
 */
void fn_800A3C4C(void* argument, Wrapper800A3C4C* wrapper, int first, int second)
{
    Object800A3C4C* object = wrapper->object;
    Vtable800A3C4C* vtable = object->vtable;
    Callback800A3C4C callback = vtable->callback;

    callback(object, argument, first, second);
}
