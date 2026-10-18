typedef unsigned char u8;

extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern double lua_tonumber(void*, int);
extern int fn_801B0B30(int);
extern void fn_801B05B0(int, u8);
extern const char lbl_8024FF00[];
extern const char lbl_8024FF30[];

int fn_8016C3B4(void* state)
{
    int object;
    int value;
    u8 byte_value;

    if (lua_gettop(state) != 2) {
        luaO_verror(state, lbl_8024FF00, 2, lua_gettop(state));
        return 0;
    }

    object = (int)lua_tonumber(state, 1);
    value = (int)lua_tonumber(state, 2);
    byte_value = (value > 0 ? value : 0) > 255
                     ? 255
                     : (value > 0 ? value : 0);
    if (value != byte_value) {
        luaO_verror(state, lbl_8024FF30, value);
    } else {
        object = fn_801B0B30(object);
        if (object != -1) {
            fn_801B05B0(object, byte_value);
        }
    }
    return 0;
}
