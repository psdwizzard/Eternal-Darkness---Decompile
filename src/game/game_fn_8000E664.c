typedef int s32;

extern const char lbl_8023BEF8[];
extern s32 lbl_8064C610;
extern s32 lbl_8064D5A8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern int fn_80201B44();
extern void fn_8000E84C(s32, s32);

s32 fn_8000E664(void* script)
{
    s32 first;
    s32 second;
    s32 valid = 1;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);

    if (first == fn_80201B44()) {
        s32 current = lbl_8064D5A8;
        s32 elapsed = current - lbl_8064C610;

        if (elapsed > 120 ||
            (elapsed < 0 && elapsed + (s32)0x80000000 - 1 > 119)) {
            lbl_8064C610 = current;
        } else {
            valid = 0;
        }
    }

    if (valid) {
        fn_8000E84C(first, second);
    }
    return 0;
}
