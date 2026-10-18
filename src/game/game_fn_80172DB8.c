typedef struct RuntimeObject {
    unsigned char pad_00[0x68];
    unsigned int flags;
} RuntimeObject;

extern int lua_gettop(void*);
extern RuntimeObject* lua_touserdata(void*, int);
extern void lua_pushnumber(void*, double);
extern void luaO_verror(void*, const char*, ...);
extern const char lbl_8024FF00[];

int fn_80172DB8(void* state)
{
    int value = 0;
    RuntimeObject* object;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    object = lua_touserdata(state, 1);
    if ((object->flags & 4) != 0) {
        value = 1;
    } else if ((object->flags & 8) != 0) {
        value = 2;
    }
    lua_pushnumber(state, value);
    return 1;
}
