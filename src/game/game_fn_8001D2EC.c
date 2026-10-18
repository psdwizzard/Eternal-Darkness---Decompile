typedef int s32;
typedef float f32;

char lbl_8023CF40[24] = "EDSpecialRegionCheck";

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_800C3CE4(f32);
extern const f32 lbl_8064DE90;
extern char lbl_8023BEF8[];

s32 fn_8001D2EC(void* script)
{
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    fn_800C3CE4(lbl_8064DE90 * (f32)lua_tonumber(script, 1));
    return 0;
}
