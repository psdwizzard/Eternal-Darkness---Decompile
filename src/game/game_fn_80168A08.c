typedef struct Value {
    int type;
    int unused;
    char* data;
} Value;

extern int luaO_str2d(void*, void*);

int luaV_tonumber(Value* value)
{
    if (value->type != 3)
        return 1;
    if (luaO_str2d(value->data + 0x14, &value->data) == 0)
        return 2;
    value->type = 2;
    return 0;
}
