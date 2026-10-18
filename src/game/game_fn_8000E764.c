typedef int s32;

extern const char lbl_8023BEF8[];
extern s32 lbl_8064C614;
extern s32 lbl_8064D5A8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80201B44();
extern void fn_8000E84C(s32, s32);

s32 fn_8000E764(void* script)
{
    s32 current;
    s32 first;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    if (first == fn_80201B44()) {
        s32 elapsed;

        current = lbl_8064D5A8;
        elapsed = current - lbl_8064C614;
        if (elapsed > 120 ||
            (elapsed < 0 && elapsed + (s32)0x80000000 - 1 > 119)) {
            fn_8000E84C(first, (s32)lua_tonumber(script, 2));
            lbl_8064C614 = current;
        }
    }
    return 0;
}
