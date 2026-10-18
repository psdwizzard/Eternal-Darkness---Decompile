extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8011E26C(int);
extern void fn_8011DD8C(int, int);
extern const char lbl_8024FF00[];

int fn_80175964(void* state)
{
    int second;
    int first;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    fn_8011E26C(1);
    second = lua_tonumber(state, 2);
    first = lua_tonumber(state, 1);
    fn_8011DD8C(first, second);
    return 0;
}
