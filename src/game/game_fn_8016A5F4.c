typedef struct Value {
    int type;
    char payload[12];
} Value;

extern Value* luaA_indexAcceptable(void*, int);

int lua_type(void* context, int index)
{
    Value* value = luaA_indexAcceptable(context, index);
    if (value == 0) {
        return -1;
    }
    return value->type;
}
