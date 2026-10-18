typedef struct Value {
    int type;
    int pad04;
    void** pointer;
} Value;

extern Value* luaA_indexAcceptable(void*, int);

void* lua_touserdata(void* context, int index)
{
    Value* value = luaA_indexAcceptable(context, index);
    int invalid = value == 0 || value->type != 0;
    return invalid ? 0 : value->pointer[1];
}
