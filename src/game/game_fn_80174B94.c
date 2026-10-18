extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8012C478(void*, int, int);
extern const char lbl_8024FF00[];

int fn_80174B94(void* state)
{
    void* object;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    object = fn_80201814((int)lua_tonumber(state, 1));
    if (object != 0) {
        object = fn_80201BC8(object);
        if (object != 0) {
            fn_8012C478(object, 15, 0);
        }
    }
    return 0;
}
