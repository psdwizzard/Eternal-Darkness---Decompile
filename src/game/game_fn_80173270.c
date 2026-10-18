typedef struct Vec3s {
    short x;
    short y;
    short z;
} Vec3s;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158CC8(int, int, Vec3s*);
extern void fn_801798DC(Vec3*, float);
extern void fn_8014D478(void*, Vec3*, Vec3*, int, int, void*, int);
extern int lbl_806506E0;
extern const double lbl_806506A8;
extern const char lbl_8024FF00[];
extern const char lbl_8025009C[];

int fn_80173270(void* state)
{
    int resource;
    int arg2;
    int arg3;
    short arg8;
    int arg9;
    int index;
    Vec3s lookup;
    Vec3s* source;
    Vec3 position;
    Vec3 rotation;
    int effect = lbl_806506E0;

    if (lua_gettop(state) != 9) {
        luaO_verror(state, lbl_8024FF00, 9, lua_gettop(state));
        return 0;
    }

    resource = fn_800F5C54(lua_tonumber(state, 1));
    arg2 = lua_tonumber(state, 2);
    arg3 = lua_tonumber(state, 3);
    lua_tonumber(state, 4);
    lua_tonumber(state, 5);
    lua_tonumber(state, 6);
    lua_tonumber(state, 7);
    arg8 = lua_tonumber(state, 8);
    arg9 = lua_tonumber(state, 9);

    index = fn_8015C4A4(resource, 2);
    if (index != -1) {
        source = fn_80158CC8(index, 2, &lookup);
    } else {
        luaO_verror(state, lbl_8025009C, resource);
    }

    position.x = source->x;
    position.y = source->y;
    position.z = source->z;
    rotation.x = lookup.x;
    rotation.y = lookup.y;
    rotation.z = lookup.z;
    fn_801798DC(&rotation, arg8);
    fn_8014D478(0, &position, &rotation, arg2, arg3, &effect, arg9);
    return 0;
}
