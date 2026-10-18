typedef unsigned int u32;
typedef int s32;

char lbl_8023CDC0[] = "EDEndMainCharacterSpell";

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_80006954(u32);
extern char lbl_8023BEF8[];

s32 fn_8001CB10(void* script)
{
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    fn_80006954(fn_800F5C54(lua_tonumber(script, 1)));
    return 0;
}
