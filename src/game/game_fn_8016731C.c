typedef struct LuaState LuaState;
typedef struct HashTable HashTable;

typedef struct Value {
    int type;
    int pad4;
    union {
        double number;
        void* pointer;
    } data;
} Value;

extern Value* luaH_getany(LuaState*, HashTable*, Value*);
extern Value* luaH_getnum(HashTable*, double);
extern Value* luaH_getstr(HashTable*, void*);

Value* luaH_get(LuaState* state, HashTable* table, Value* value)
{
    switch (value->type) {
    case 2:
        return luaH_getnum(table, value->data.number);
    case 3:
        return luaH_getstr(table, value->data.pointer);
    default:
        return luaH_getany(state, table, value);
    }
}
