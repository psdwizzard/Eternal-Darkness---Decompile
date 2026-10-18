typedef struct Value {
    int type;
    int pad04;
    double number;
} Value;

extern Value* luaA_indexAcceptable(void*, int);
extern int luaV_tonumber(Value*);
extern double lbl_80650688;

double lua_tonumber(void* context, int index)
{
    int invalid;
    Value* value = luaA_indexAcceptable(context, index);
    invalid = value == 0 || (value->type != 2 && luaV_tonumber(value) != 0);
    return invalid ? lbl_80650688 : value->number;
}
