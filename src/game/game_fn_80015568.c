typedef int s32;
typedef signed short s16;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

extern const char lbl_8023BEF8[];
char lbl_8023CAEC[] = " (Error: pCentreVert is NULL)";
extern const double lbl_8064DCE8;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void* lua_touserdata(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801D38BC(s32, void*, void*);
extern void fn_8014F5B8(Vec3f*, s32, s16, s32, float, void*);

s32 fn_80015568(void* script)
{
    s16* position;
    s32 second;
    s32 third;
    float fourth;
    Vec3f vector;
    s16 transformed_short;
    s32 transformed_word;
    s32 transformed_copy;

    if (lua_gettop(script) != 4) {
        luaO_verror(script, lbl_8023BEF8, 4, lua_gettop(script));
        return 0;
    }

    position = lua_touserdata(script, 1);
    second = (s32)lua_tonumber(script, 2);
    third = (s32)lua_tonumber(script, 3);
    fourth = (float)lua_tonumber(script, 4);

    if (position == 0) {
        luaO_verror(script, lbl_8023CAEC, 0);
    }

    vector.x = position[0];
    vector.y = position[1];
    vector.z = position[2];
    transformed_short = 5;
    fn_801D38BC(third, &transformed_word, &transformed_short);
    transformed_copy = transformed_word;
    fn_8014F5B8(&vector, second, transformed_short, 0, fourth,
                &transformed_copy);
    return 0;
}
