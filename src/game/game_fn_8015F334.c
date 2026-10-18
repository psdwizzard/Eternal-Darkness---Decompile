typedef struct ObjectData {
    char pad0[0x18];
    unsigned int* entries;
} ObjectData;

typedef struct Object {
    ObjectData* data;
    char pad4[0xC];
    int count;
} Object;

typedef struct Command {
    int type;
    int first;
    int second;
} Command;

extern void discharge1(Object*, Command*);
extern int luaK_code1(Object*, int, int);
extern int invertjump(int);
extern void luaK_concat(Object*, int*, int);
extern int luaK_getlabel(Object*);
extern void luaK_patchlist(Object*, int, int);

#pragma use_lmw_stmw on

void luaK_testgo(Object* object, Command* command, int use_second, int type)
{
    int index;
    int* output;
    int* input;
    unsigned int* entries;
    unsigned int offset;
    int entry_type;

    if (use_second == 0) {
        output = &command->second;
        input = &command->first;
    } else {
        output = &command->first;
        input = &command->second;
    }

    discharge1(object, command);
    index = object->count - 1;
    entries = object->data->entries;
    offset = (unsigned int)index * 4;
    entry_type = entries[index] & 0x3F;
    if (entry_type < 32 || entry_type > 42) {
        index = luaK_code1(object, type, -1);
    } else if (use_second != 0) {
        entries[index] = (entries[index] & ~0x3F) | invertjump(entry_type);
    }

    luaK_concat(object, input, index);
    luaK_patchlist(object, *output, luaK_getlabel(object));
    *output = -1;
}
