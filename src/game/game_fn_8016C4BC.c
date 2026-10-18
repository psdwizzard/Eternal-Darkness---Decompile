typedef signed short s16;

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern s16* lua_touserdata(void*, int);
extern int fn_801B05E8(int, int, int, int, void*, int, int, int);
extern void fn_801B0D30(void);
extern const char lbl_8024FF00[];
extern int lbl_8064D18C;

int fn_8016C4BC(void* state)
{
    int first;
    void* position;
    int second;
    int third;
    int fourth;
    s16* source;
    float vector[3];
    int result;

    if (lua_gettop(state) != 5) {
        luaO_verror(state, lbl_8024FF00, 5, lua_gettop(state));
        return 0;
    }

    first = (int)lua_tonumber(state, 1);
    second = (int)lua_tonumber(state, 2);
    third = (int)lua_tonumber(state, 3);
    fourth = (int)lua_tonumber(state, 4);
    source = lua_touserdata(state, 5);
    if (source != 0) {
        vector[0] = source[0];
        vector[1] = source[1];
        vector[2] = source[2];
        position = vector;
    } else {
        position = 0;
        third = 5;
    }

    result = fn_801B05E8(first, second, fourth, 1, position, third, 0, 1);
    if (result == -1 && first == 493 && lbl_8064D18C == 39) {
        fn_801B0D30();
        fn_801B05E8(first, second, fourth, 1, position, third, 0, 1);
    }
    return 0;
}
