typedef signed short s16;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80179DB0(Vec3*, Vec3s*);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8011F0E8(void*, Vec3*);
extern const char lbl_8024FF00[];

int fn_8016F400(void* state)
{
    Vec3 position;
    int object_id;
    Vec3s* source;
    void* object;

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
    if (object != 0) {
        object = fn_80201BC8(object);
        if (object != 0) {
            fn_8011F0E8(object, &position);
        }
    }
    return 0;
}
