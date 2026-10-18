extern void luaV_Cclosure(void*);

void lua_pushcclosure(void* context)
{
    luaV_Cclosure(context);
}
