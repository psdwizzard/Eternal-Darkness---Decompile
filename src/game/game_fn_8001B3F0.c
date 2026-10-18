typedef unsigned char u8;
typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201B8C();

s32 fn_8001B3F0(void* script)
{
    s32 id;
    s32 value;
    void* manager;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    id = lua_tonumber(script, 1);
    value = lua_tonumber(script, 2);
    if (fn_80201814(id) != 0) {
        manager = fn_80201B8C();
        if (*((u8*)manager + 0x9E) == 1) {
            *((u8*)*(void**)manager + 0x93) = value;
        }
    }
    return 0;
}
