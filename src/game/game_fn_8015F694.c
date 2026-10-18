typedef struct ObjectData {
    char pad0[0x18];
    unsigned int* entries;
} ObjectData;

typedef struct Object {
    ObjectData* data;
    char pad4[0xC];
    int count;
} Object;

typedef struct OuterObject {
    char pad0[0x28];
    Object* object;
} OuterObject;

typedef struct Command {
    int type;
    int first;
    int second;
} Command;

extern void luaK_tostack(OuterObject*, Command*, int);
extern void luaK_code0(Object*, int);
extern void discharge1(Object*, Command*);
extern int invertjump(int);

void luaK_prefix(OuterObject* outer, int alternate, Command* command)
{
    Object* object = outer->object;

    if (alternate == 0) {
        luaK_tostack(outer, command, 1);
        luaK_code0(object, 30);
    } else {
        unsigned int* entries;
        unsigned int offset;
        int type;
        int temp;

        discharge1(object, command);
        entries = object->data->entries;
        offset = (object->count - 1) * 4;
        type = entries[offset / 4] & 0x3F;
        if (type >= 32 && type <= 42) {
            entries[offset / 4] = (entries[offset / 4] & ~0x3F) |
                                  invertjump(type);
        } else {
            luaK_code0(object, 31);
        }

        temp = command->second;
        command->second = command->first;
        command->first = temp;
    }
}
