typedef struct Vec3s {
    short x;
    short y;
    short z;
} Vec3s;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern Vec3s* lua_touserdata(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern int fn_801AC9F4(unsigned short, unsigned char, Vec3f*, signed char);
extern const char lbl_8024FF00[];
extern const char lbl_8025038C[];

int fn_801726EC(void* state)
{
    int first;
    int second;
    Vec3s* position;
    int fourth;
    unsigned short arg1;
    unsigned char clamped;
    Vec3f converted;
    int result;

    if (lua_gettop(state) != 4) {
        luaO_verror(state, lbl_8024FF00, 4, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    position = lua_touserdata(state, 3);
    fourth = (int)lua_tonumber(state, 4);

    arg1 = (unsigned short)first;
    clamped = (second > 0 ? second : 0) > 0x7F
                  ? 0x7F
                  : (second > 0 ? second : 0);
    if (second != clamped) {
        luaO_verror(state, lbl_8025038C, second);
    }

    converted.x = position->x;
    converted.y = position->y;
    converted.z = position->z;
    result = fn_801AC9F4(arg1, clamped, &converted, (signed char)fourth);
    lua_pushnumber(state, result);
    return 1;
}
