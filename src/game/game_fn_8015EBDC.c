typedef struct Owner {
    unsigned char pad0[0x18];
    unsigned int* entries;
} Owner;

typedef struct Object {
    Owner* owner;
} Object;

int luaK_getjump(Object* object, int index)
{
    int result = -1;
    int offset = (object->owner->entries[index] >> 6) - 0x2000000 + 1;
    if (offset != -1) {
        result = index + offset;
        result++;
    }
    return result;
}
