typedef unsigned int u32;

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void* fn_8012C62C(void*, int, u32*, u32*, u32*, int);
extern const char lbl_8024FF00[];
extern const u32 lbl_80651CB0;
extern const u32 lbl_80651CB4;
extern const u32 lbl_80651CB8;

int fn_8017583C(void* state)
{
    u32 first;
    u32 second;
    u32 third;
    void* runtime;
    void* object;

    if (lua_gettop(state) != 1) {
        luaO_verror(state, lbl_8024FF00, 1, lua_gettop(state));
        return 0;
    }

    runtime = fn_80201814((int)lua_tonumber(state, 1));
    if (runtime != 0) {
        object = fn_80201BC8();
        third = lbl_80651CB8;
        second = lbl_80651CB4;
        first = lbl_80651CB0;
        fn_8012C62C(object, 15, &first, &second, &third, 4);
    }
    return 0;
}
