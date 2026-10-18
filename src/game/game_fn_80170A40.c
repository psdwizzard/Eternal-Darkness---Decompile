typedef signed short s16;
typedef unsigned short u16;

typedef struct Entry {
    s16 id;
    u16 value2;
    u16 value4;
    u16 value6;
} Entry;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void lua_pushnumber(void*, double);
extern int lbl_8064D1BC;
extern Entry lbl_805FAA60[10];
extern const char lbl_80250198[];
extern const double lbl_806506D0;

int fn_80170A40(void* state)
{
    s16 id = lbl_8064D1BC;
    int i = 0;

    if (lua_gettop(state) > 1) {
        luaO_verror(state, lbl_80250198, lua_gettop(state));
        return 0;
    }

    if (lua_gettop(state) > 0) {
        id = lua_tonumber(state, 2);
    }

    while (lbl_805FAA60[i].id != id && i < 10) {
        i++;
    }

    if (i >= 10) {
        lua_pushnumber(state, lbl_806506D0);
    } else {
        lua_pushnumber(state, (double)lbl_805FAA60[i].value2);
    }
    return 1;
}
