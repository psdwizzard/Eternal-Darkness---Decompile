typedef int s32;

extern s32 fn_800DE354(void);
extern void lua_pushnumber(void*, double);

int fn_8000D3D4(void* script)
{
    s32 value = fn_800DE354();

    lua_pushnumber(script, (double)value);
    return 1;
}
