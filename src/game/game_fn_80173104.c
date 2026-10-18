typedef struct ShortVector {
    short x;
    short y;
    short z;
} ShortVector;

extern int lua_gettop(void*);
extern void* lua_touserdata(void*, int);
extern void lua_pushusertag(void*, void*, int);
extern void luaO_verror(void*, const char*, ...);
extern ShortVector lbl_8064D1EC;
extern const char lbl_8024FF00[];
extern const char lbl_8025047C[];

int fn_80173104(void* state)
{
    ShortVector* first;
    ShortVector* second;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    first = lua_touserdata(state, 1);
    second = lua_touserdata(state, 2);
    if (first == 0 || second == 0) {
        luaO_verror(state, lbl_8025047C, first, second);
    }
    lbl_8064D1EC.x = first->x + second->x;
    lbl_8064D1EC.y = first->y + second->y;
    lbl_8064D1EC.z = first->z + second->z;
    lua_pushusertag(state, &lbl_8064D1EC, 0);
    return 1;
}
