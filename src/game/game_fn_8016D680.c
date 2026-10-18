extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void fn_80201138(int, void*, int, int, int, float);
extern const char lbl_8024FF00[];

int fn_8016D680(void* state)
{
    int a;
    int b;
    int x;
    int y;
    float z;
    int c;

    if (lua_gettop(state) != 6) {
        luaO_verror(state, lbl_8024FF00, 6, lua_gettop(state));
        return 0;
    }
    x = (int)lua_tonumber(state, 1);
    y = (int)lua_tonumber(state, 2);
    z = (float)lua_tonumber(state, 3);
    a = (int)lua_tonumber(state, 4);
    b = (int)lua_tonumber(state, 5);
    c = (int)lua_tonumber(state, 6);
    if (x != 0) {
        void* object = fn_80201814(x);
        if (object != 0) {
            fn_80201138(y, object, a, b, c, z);
        }
    }
    return 0;
}
