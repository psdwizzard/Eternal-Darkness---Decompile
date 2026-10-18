typedef int s32;

extern s32 fn_80128328(void);
extern void lua_pushnumber(void*, double);

s32 fn_8000B1B8(void* script)
{
    s32 value = fn_80128328();
    lua_pushnumber(script, value);
    return 1;
}
