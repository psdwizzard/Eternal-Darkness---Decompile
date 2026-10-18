extern void lua_tostring(void*, int);

int errormessage(void* context)
{
    lua_tostring(context, 1);
    return 0;
}
