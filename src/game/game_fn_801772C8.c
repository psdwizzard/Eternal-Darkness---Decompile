typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801F6FD8(Vec3);
extern const char lbl_8024FF00[];

int fn_801772C8(void* state)
{
    Vec3 value;

    if (lua_gettop(state) != 3) {
        luaO_verror(state, lbl_8024FF00, 3, lua_gettop(state));
        return 0;
    }

    value.x = (float)lua_tonumber(state, 1);
    value.y = (float)lua_tonumber(state, 2);
    value.z = (float)lua_tonumber(state, 3);
    fn_801F6FD8(value);
    return 1;
}
