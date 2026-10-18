typedef int s32;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern volatile s32 lbl_8064B818;

s32 fn_8000D8A4(void* script)
{
    s32 value;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    switch (value) {
    case -1:
        lbl_8064B818 = value;
        break;
    case 0:
        lbl_8064B818 = value;
        break;
    case 1:
        lbl_8064B818 = value;
        break;
    case 2:
        lbl_8064B818 = value;
        break;
    case 3:
        lbl_8064B818 = value;
        break;
    case 4:
        lbl_8064B818 = value;
        break;
    case 5:
        lbl_8064B818 = value;
        break;
    }
    return 0;
}
