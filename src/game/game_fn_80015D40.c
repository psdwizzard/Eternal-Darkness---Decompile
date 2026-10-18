typedef int s32;
typedef signed short s16;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern const char lbl_8023BEF8[];
char lbl_8023CB2C[] =
    "\n(Error: pStartVert is NULL)\n\0\0\0"
    " (Error: pDirectionVert is NULL)\0\0\0";
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_80153D04(Vec3f*, s32, s32, s32, s32, s32, s32, s32, s32);

s32 fn_80015D40(void* script)
{
    s16* position;
    s32 second;
    s32 third;
    s32 fourth;
    s32 fifth;
    s32 sixth;
    s32 seventh;
    s32 eighth;
    Vec3f vector;

    if (lua_gettop(script) != 8) {
        luaO_verror(script, lbl_8023BEF8, 8, lua_gettop(script));
        return 0;
    }

    position = lua_touserdata(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (s32)lua_tonumber(script, 4);
    fifth = (s32)lua_tonumber(script, 5);
    sixth = (s32)lua_tonumber(script, 6);
    seventh = (s32)lua_tonumber(script, 7);
    eighth = (s32)lua_tonumber(script, 8);

    if (position == 0) {
        luaO_verror(script, lbl_8023CB2C, 0);
    }

    vector.x = position[0];
    vector.y = position[1];
    vector.z = position[2];
    fn_80153D04(&vector, second, third, fourth, fifth, sixth, seventh, eighth, 4);
    return 0;
}
