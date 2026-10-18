extern int lua_type(void*, int);

int lua_isstring(void* context, int index)
{
    int type = lua_type(context, index);
    return type == 2 || type == 3;
}
