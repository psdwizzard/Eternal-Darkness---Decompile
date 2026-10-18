typedef int s32;
typedef unsigned int u32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_801D0050(s32, u32*);

s32 fn_80013AD4(void* script)
{
    void* parser = script;
    u32 value;
    u32 second;
    u32 combined;

    if (lua_gettop(parser) != 3) {
        luaO_verror(parser, lbl_8023BEF8, 3, lua_gettop(parser));
        return 0;
    }

    value = fn_800F5C54(lua_tonumber(parser, 1));
    second = fn_800F5C54(lua_tonumber(parser, 2));
    combined = second | fn_800F5C54(lua_tonumber(parser, 3));
    combined |= 0x40000000;
    value |= combined;
    fn_801D0050(1, &value);
    return 0;
}
