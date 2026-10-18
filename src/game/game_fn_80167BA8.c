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

extern Value* luaH_set(LuaState*, HashTable*, Value*);

void luaH_setstrnum(LuaState* state, HashTable* table, void* key, double number)
{
    Value value;
    Value* result;

    value.type = 3;
    value.data.pointer = key;
    result = luaH_set(state, table, &value);
    result->type = 2;
    result->data.number = number;
}
