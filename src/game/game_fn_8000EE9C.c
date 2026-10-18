typedef int s32;

extern const char lbl_8023BEF8[];
extern void fn_8000755C(s32, s32, s32);
extern void fn_80138F78(s32);
extern void luaO_verror(void*, const char*, ...);
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern int fn_80201B44();

s32 fn_8000EE9C(void* script)
{
    s32 mapped;
    s32 value;

    fn_80201B44();
    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    value = (s32)lua_tonumber(script, 1);
    switch (value) {
    case 26:
        mapped = 9;
        break;
    case 1:
        mapped = 0;
        break;
    case 27:
        mapped = 150;
        break;
    case 44:
        mapped = 18;
        break;
    case 53:
        mapped = 69;
        break;
    case 49:
        mapped = 70;
        break;
    case 55:
        mapped = 73;
        break;
    case 47:
        mapped = 74;
        break;
    case 45:
        mapped = 75;
        break;
    case 54:
        mapped = 76;
        break;
    case 48:
        mapped = 81;
        break;
    case 46:
        mapped = 85;
        break;
    default:
        mapped = 9;
        break;
    }

    fn_80138F78(1);
    fn_8000755C(mapped, value, 0);
    return 0;
}
