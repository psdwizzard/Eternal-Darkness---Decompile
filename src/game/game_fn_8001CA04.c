typedef unsigned int u32;
typedef int s32;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnil(void*);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern u32 fn_8004519C(void);
extern s32 fn_800451E4(s32);
char lbl_8023CD70[] = "\nInvalid Alignment of %i\n";
char lbl_8023CD8C[] =
    "\nInvalid Num of Args Expecting 0 or 1, and got %i\n";
extern double lbl_8064DE60;
extern double lbl_8064DCF8;

s32 fn_8001CA04(void* script)
{
    s32 mode;
    switch (lua_gettop(script)) {
    case 0:
        lua_pushnumber(script, (double)fn_8004519C());
        break;
    case 1:
        mode = (s32)lua_tonumber(script, 1);
        switch (mode) {
        case 1:
        case 2:
        case 3:
            if (fn_800451E4(mode) != 0) {
                lua_pushnumber(script, lbl_8064DCF8);
            } else {
                lua_pushnil(script);
            }
            break;
        default:
            luaO_verror(script, lbl_8023CD70, mode);
            return 0;
        }
        break;
    default:
        luaO_verror(script, lbl_8023CD8C, lua_gettop(script));
        return 0;
    }
    return 1;
}
