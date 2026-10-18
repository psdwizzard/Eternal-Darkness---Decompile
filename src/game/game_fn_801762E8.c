extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
typedef struct Object Object;
extern void *fn_80201C24();
extern unsigned short fn_80157948(Object*);
extern unsigned short fn_80157994(Object*);
extern const char lbl_8024FF00[];

int fn_801762E8(void* state)
{
    Object* object;
    unsigned short first;
    int object_id;
    int value;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    if (fn_80201814(object_id) != 0) {
        object = fn_80201C24();
        first = fn_80157948(object);
        value = first - fn_80157994(object);
        lua_pushnumber(state, (double)value);
    } else {
        lua_pushnumber(state, -1.0);
    }
    return 1;
}
