extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern unsigned int fn_8011FA8C(void*, int, int);
extern const char lbl_8024FF00[];

int fn_80177034(void* state)
{
    int first;
    int second;
    void* object;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    object = fn_80201BC8(fn_80201814(first));
    if (second != 0) {
        fn_8011FA8C(object, 0x800, 0);
    } else {
        fn_8011FA8C(object, 0, 0x800);
    }
    return 1;
}
