typedef signed short s16;
typedef unsigned char u8;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern int fn_8015C4A4(int, int);
extern Vec3s* fn_80158ABC(int, int, void*);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern u8 fn_8012B8A8(void*, const Vec3f*);
extern void lua_pushnumber(void*, double);
extern void lua_pushusertag(void*, void*, int);
extern const char lbl_8024FF00[];
extern const double lbl_806506A8;

int fn_801711D0(void* state)
{
    register const char* strings = lbl_8024FF00;
    int object_id;
    void* object;
    int handle;
    int index;
    Vec3s* packed;
    Vec3f position;
    u8 result;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, strings, 2, lua_gettop(state));
        return 0;
    }

    object_id = (int)lua_tonumber(state, 1);
    object = fn_80201814(object_id);
    if (object != 0) {
        handle = fn_800F5C54(lua_tonumber(state, 2));
        index = fn_8015C4A4(handle, 2);
        if (index != -1) {
            packed = fn_80158ABC(index, 2, &result);
            position.x = packed->x;
            position.y = packed->y;
            position.z = packed->z;
            object = fn_80201BC8(object);
            lua_pushnumber(state, (int)fn_8012B8A8(object, &position));
        } else {
            luaO_verror(state, strings + 412, handle);
            lua_pushusertag(state, 0, 0);
        }
    } else {
        luaO_verror(state, strings + 796, object_id);
        lua_pushusertag(state, 0, 0);
    }
    return 1;
}
