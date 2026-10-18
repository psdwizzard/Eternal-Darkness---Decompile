typedef int s32;

extern const char lbl_8023BEF8[];
extern void* lbl_8064C4E4;
extern void* lbl_8064C528;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern s32 fn_8011FCE4(void*);
extern void* fn_801E86A0(void*, s32);
extern void fn_8011F938(void*, void*);
extern void fn_8011EAF4(void*, s32);
extern void fn_801387E4(s32);
extern void fn_801387EC(s32);
extern void fn_801261C4(void*);

s32 fn_8000D44C(void* script)
{
    s32 index;
    s32 value;
    void* object;

    if (lua_gettop(script) != 1) {
        luaO_verror(script, lbl_8023BEF8, 1, lua_gettop(script));
        return 0;
    }

    index = (s32)lua_tonumber(script, 1);
    if (index != -1) {
        value = fn_8011FCE4(lbl_8064C4E4);
        object = fn_801E86A0(lbl_8064C528, index);
        fn_8011F938(lbl_8064C4E4, object);
        fn_8011EAF4(lbl_8064C4E4, index);
        fn_801387E4(index);
        fn_801387EC(value);
        fn_801261C4(lbl_8064C4E4);
    }
    return 0;
}
