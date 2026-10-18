typedef int s32;

extern const char lbl_8023BEF8[];

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern unsigned int fn_8011FA8C(void*, int, int);

s32 fn_8001A2A4(void* script)
{
    s32 first;
    s32 second;
    void* object;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    if (fn_80201814(first) != 0 && (object = fn_80201BC8()) != 0) {
        if (second != 0) {
            fn_8011FA8C(object, 0, 0x04000000);
        } else {
            fn_8011FA8C(object, 0x04000000, 0);
        }
    }
    return 0;
}
