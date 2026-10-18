typedef struct Owner {
    unsigned char pad0[0x18];
    unsigned int* entries;
} Owner;

typedef struct Object {
    Owner* owner;
    unsigned char pad4[0xC];
    int current;
} Object;

extern int luaK_lastisopen(Object*);
extern void luaK_deltastack(Object*, int);

void luaK_setcallreturns(Object* object, int value)
{
    if (luaK_lastisopen(object)) {
        Owner* owner;
        int index;
        unsigned int shifted;
        unsigned int* entry;

        owner = object->owner;
        shifted = value << 6;
        index = object->current;
        entry = &owner->entries[index];
        entry[-1] = shifted | (entry[-1] & ~0x7FC0U);
        luaK_deltastack(object, value);
    }
}
