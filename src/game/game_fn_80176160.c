extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201C24();
typedef struct Object Object;
extern unsigned int fn_80157BF4(Object*);
extern const char lbl_8024FF00[];

int fn_80176160(void* state)
{
    int object_id;
    unsigned int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    if (fn_80201814(object_id) != 0) {
        value = fn_80157BF4(fn_80201C24());
        lua_pushnumber(state, (double)value);
    } else {
        lua_pushnumber(state, -1.0);
    }
    return 1;
}
