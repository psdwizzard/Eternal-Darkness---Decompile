typedef int s32;

extern s32 fn_800CAB80(void);
extern int lua_gettop(void*);
extern void lua_pushnumber(void*, double);

s32 fn_8000E054(void* script)
{
    s32 value;

    lua_gettop(script);
    value = fn_800CAB80();
    lua_pushnumber(script, (double)value);
    return 1;
}
