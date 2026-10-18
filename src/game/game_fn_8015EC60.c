typedef struct Owner {
    unsigned char pad0[0x24];
    short limit;
} Owner;

typedef struct Object {
    Owner* owner;
    unsigned char pad4[4];
    void* value;
    unsigned char padC[0x10];
    short count;
} Object;

extern char lbl_8024F25C[];
extern void luaK_error(void*, void*);

void luaK_deltastack(Object* object, int amount)
{
    object->count += amount;
    if (object->count > object->owner->limit) {
        if (object->count > 250)
            luaK_error(object->value, lbl_8024F25C);
        object->owner->limit = object->count;
    }
}
