typedef struct LuaState LuaState;
typedef struct HashTable HashTable;
typedef struct Value Value;

typedef struct HashNode {
    char pad0[0x10];
    Value* result;
    char pad14[0xC];
    struct HashNode* next;
} HashNode;

extern HashNode* luaH_mainposition(HashTable*, Value*);
extern int luaO_equalObj(Value*, HashNode*);
extern void lua_error(LuaState*, const char*);
extern const char lbl_8024FA48[];
extern Value luaO_nilobject;

Value* luaH_getany(LuaState* state, HashTable* table, Value* value)
{
    HashNode* node = luaH_mainposition(table, value);

    if (node == 0) {
        lua_error(state, lbl_8024FA48);
    } else {
        do {
            if (luaO_equalObj(value, node)) {
                return (Value*)((char*)node + 0x10);
            }
            node = node->next;
        } while (node != 0);
    }
    return &luaO_nilobject;
}
