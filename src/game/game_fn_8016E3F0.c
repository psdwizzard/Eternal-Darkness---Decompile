extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern void luaO_verror(void*, const char*, ...);
extern void fn_801FA198(unsigned int, void*, int, int, int, int, int, int, int);
extern const char lbl_8024FF00[];
extern char lbl_8063CD18[];

int fn_8016E3F0(void* state)
{
    int second;
    int fourth;
    int third;
    unsigned int first;
    int fifth;

    if (lua_gettop(state) != 5) {
        luaO_verror(state, lbl_8024FF00, 5, lua_gettop(state));
        return 0;
    }
    first = fn_800F5C54(lua_tonumber(state, 1));
    second = (int)lua_tonumber(state, 2);
    third = (int)lua_tonumber(state, 3);
    fourth = (int)lua_tonumber(state, 4);
    fifth = (int)lua_tonumber(state, 5);
    fn_801FA198(first, lbl_8063CD18 + 0x110, second, third, fourth, 0, 0, fifth, 0);
    return 0;
}
