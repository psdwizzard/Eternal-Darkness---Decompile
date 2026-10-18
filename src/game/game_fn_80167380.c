typedef struct LuaState LuaState;

typedef struct Value {
    int type;
    int pad4;
    char data[8];
} Value;

typedef struct HashNode {
    char pad0[0x10];
    Value value;
    char pad20[8];
} HashNode;

typedef struct HashTable {
    HashNode* nodes;
    int pad4;
    int size;
} HashTable;

extern Value* luaH_get(LuaState*, HashTable*, Value*);
extern void lua_error(LuaState*, const char*);
extern Value luaO_nilobject;
extern const char lbl_8024FA5C[];

HashNode* luaH_next(LuaState* state, HashTable* table, Value* value)
{
    Value* found;
    int offset;
    int index;

    if (value->type == 1) {
        index = 0;
    } else {
        found = luaH_get(state, table, value);
        if (found == &luaO_nilobject) {
            lua_error(state, lbl_8024FA5C);
        }
        index = ((unsigned int)found - ((unsigned int)table->nodes + 0x10)) / 40 + 1;
    }

    offset = index * 40;
    for (; index < table->size; index++, offset += 40) {
        HashNode* node = (HashNode*)((char*)table->nodes + offset);
        if (node->value.type != 1) {
            return node;
        }
    }
    return 0;
}
