typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80179DB0(Vec3*, void*);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern float fn_8012B7D0(void*, Vec3*);
extern const char lbl_8024FF00[];
extern const float lbl_806506C4;

int fn_8016F8F8(void* state)
{
    int object_id;
    void* source;
    void* object;
    Vec3 position;
    Vec3 copy;
    float value;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    source = lua_touserdata(state, 2);
    if (source != 0) {
        fn_80179DB0(&position, source);
    } else {
        return 0;
    }

    object = fn_80201814(object_id);
    if (object != 0 && fn_80201BC8(object) != 0) {
        object = fn_80201BC8(object);
        copy = position;
        value = fn_8012B7D0(object, &copy);
        lua_pushnumber(state, lbl_806506C4 * value);
    } else {
        return 0;
    }
    return 1;
}
