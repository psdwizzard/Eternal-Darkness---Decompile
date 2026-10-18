typedef unsigned short u16;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern unsigned int fn_800F5C54(double);
extern void fn_8016D9C0(unsigned int, u16*, u16*);
extern void fn_801F6198(void*, u16, u16);
extern const char lbl_8024FF00[];

int fn_8016DA80(void* state)
{
    void* object;
    int type;
    u16 second;
    u16 first;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    object = (void *)fn_800F5C54(lua_tonumber(state, 1));
    type = (int)lua_tonumber(state, 2);
    if (object != 0) {
        fn_8016D9C0(type, &first, &second);
        fn_801F6198(object, first, second);
    }
    return 1;
}
