extern int lua_gettop(void*);
extern int lua_isstring(void*, int);
extern void* lua_type(void*, int);
extern void* lua_typename(void*, void*);
extern int fn_800FD228(void*, const char*);
extern const char lbl_8024FFF8[];

int fn_8016E7B8(void* state)
{
    int count = lua_gettop(state);
    int i;

    for (i = 1; i <= count; i++) {
        if (lua_isstring(state, i) == 0) {
            fn_800FD228(lua_typename(state, lua_type(state, i)), lbl_8024FFF8);
        }
    }
    return 0;
}
