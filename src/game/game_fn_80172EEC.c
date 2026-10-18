typedef struct ShortVector {
    short x;
    short y;
    short z;
} ShortVector;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void lua_pushusertag(void*, void*, int);
extern void luaO_verror(void*, const char*, ...);
extern ShortVector lbl_805FC2E8[];
extern const char lbl_8024FF00[];

int fn_80172EEC(void* state)
{
    int index;
    int x;
    int y;
    int z;
    ShortVector* vector;

    if (lua_gettop(state) != 4) {
        luaO_verror(state, lbl_8024FF00, 4, lua_gettop(state));
        return 0;
    }

    index = lua_tonumber(state, 1);
    x = lua_tonumber(state, 2);
    y = lua_tonumber(state, 3);
    z = lua_tonumber(state, 4);
    vector = &lbl_805FC2E8[index];
    vector->x = x;
    vector->y = y;
    vector->z = z;
    lua_pushusertag(state, vector, 0);
    return 1;
}
