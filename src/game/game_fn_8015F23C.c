typedef struct ObjectData {
    char pad0[0x18];
    int* entries;
} ObjectData;

typedef struct Object {
    ObjectData* data;
} Object;

extern int luaK_getjump(Object*, int);

int need_value(Object* object, int index, int type)
{
    while (index != -1) {
        if ((object->data->entries[index] & 0x3F) != type) {
            return 1;
        }
        index = luaK_getjump(object, index);
    }
    return 0;
}
