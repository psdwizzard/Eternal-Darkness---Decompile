typedef struct ObjectData {
    char pad0[0x18];
    unsigned int* entries;
} ObjectData;

typedef struct Object {
    ObjectData* data;
} Object;

extern int luaK_getjump(Object*, int);
extern void luaK_fixjump(Object*, int, int);

#pragma use_lmw_stmw on

void luaK_patchlistaux(Object* object, int index, int value, int match, int replacement)
{
    unsigned int* entries = object->data->entries;

    while (index != -1) {
        int next = luaK_getjump(object, index);
        int type = entries[index] & 0x3F;

        if (type == match) {
            luaK_fixjump(object, index, replacement);
        } else {
            luaK_fixjump(object, index, value);
            if (type == 40) {
                entries[index] = (entries[index] & ~0x3F) | 38;
            } else if (type == 41) {
                entries[index] = (entries[index] & ~0x3F) | 39;
            }
        }
        index = next;
    }
}
