typedef struct Value {
    int type;
    int pad04;
    void* pointer;
} Value;

extern Value* luaA_indexAcceptable(void*, int);
extern int luaV_tostring(void*, Value*);

void* lua_tostring(void* context, int index)
{
    Value* value = luaA_indexAcceptable(context, index);
    int invalid = value == 0 ||
                  (value->type != 3 && luaV_tostring(context, value) != 0);
    return invalid ? 0 : (char*)value->pointer + 20;
}
