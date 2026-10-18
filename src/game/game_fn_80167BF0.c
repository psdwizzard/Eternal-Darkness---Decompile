typedef struct Value Value;
typedef struct HashTable HashTable;

typedef struct LuaState {
    char pad0[0x44];
    HashTable* table;
} LuaState;

extern Value* luaS_new(LuaState*, const char*);
extern Value* luaH_getstr(HashTable*, Value*);

Value* luaH_getglobal(LuaState* state, const char* name)
{
    return luaH_getstr(state->table, luaS_new(state, name));
}
