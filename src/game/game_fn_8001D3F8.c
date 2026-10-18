typedef int s32;
typedef unsigned int u32;
typedef unsigned long long u64;

char lbl_8023CF6C[16] = "EDOkayToSeek";

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern unsigned long long fn_8020123C();
extern void lua_pushnumber(void*, double);
extern void lua_pushnil(void*);
extern const double lbl_8064DCF8;
extern char lbl_8023BEF8[];

s32 fn_8001D3F8(void* script)
{
    s32 id;
    u32 message_result;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    id = (s32)lua_tonumber(script, 1);
    if (fn_80201814(id) != 0) {
        message_result = fn_8020123C(31, id, id, 0) & 0xFFFFFFFFULL;
        if (message_result != 0) {
            lua_pushnumber(script, lbl_8064DCF8);
        } else {
            lua_pushnil(script);
        }
    }
    return 1;
}
