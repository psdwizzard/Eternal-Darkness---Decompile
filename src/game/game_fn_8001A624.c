typedef int s32;

extern s32 lbl_8064C9FC;
extern const char lbl_8023CC30[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_800B9454(s32, s32);

s32 fn_8001A624(void* script)
{
    switch (lua_gettop(script)) {
    case 0:
        lbl_8064C9FC = 0;
        break;
    case 1:
        lbl_8064C9FC = (s32)lua_tonumber(script, 1);
        break;
    default:
        luaO_verror(script, lbl_8023CC30, lua_gettop(script));
        break;
    }
    fn_800B9454(1, 0);
    return 0;
}
