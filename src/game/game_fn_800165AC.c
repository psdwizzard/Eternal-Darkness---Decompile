typedef int s32;

extern const char lbl_8023BEF8[];
char lbl_8023CB70[] = "Invalid Cinematic Number: %d";
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80052580(s32, s32, s32, s32, s32);

s32 fn_800165AC(void* script)
{
    s32 value;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    if (value < 0) {
        luaO_verror(script, lbl_8023CB70, value);
    }
    fn_80052580(2, value, 1, -1, 0);
    return 0;
}
