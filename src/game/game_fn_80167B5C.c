typedef struct LuaState LuaState;
typedef struct HashTable HashTable;

typedef struct Value {
    int type;
    int pad4;
    double data;
} Value;

extern Value* luaH_set(LuaState*, HashTable*, Value*);

Value* luaH_setint(LuaState* state, HashTable* table, int key)
{
    Value value;

    value.type = 2;
    value.data = (double)key;
    return luaH_set(state, table, &value);
}
