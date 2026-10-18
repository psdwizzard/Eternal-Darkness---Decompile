extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void* fn_8017AF64(void);
extern void fn_8017AF78(void);
extern int CARDMount(int, void*, int);
extern int CARDFormat(int);
extern int CARDUnmount(int);
extern void fn_8017BA60(const char*, int);

int fn_80176A94(void* state)
{
    void* handle;
    int id;
    int result;

    handle = fn_8017AF64();
    if (lua_gettop(state) != 1) {
        luaO_verror(state, "\nInvalid Num of Args Expecting %i, and got %i\n", 1, lua_gettop(state));
        return 0;
    }

    result = (int)lua_tonumber(state, 1);
    id = result;
    result = CARDMount(id, handle, 0);
    if (result == 0 || result == -6) {
        result = CARDFormat(id);
        if (result == 0) {
            int name = CARDUnmount(id);
            if (name != 0) {
                fn_8017BA60("Couldn't unmount: ", name);
            }
        } else {
            fn_8017BA60("Couldn't format: ", result);
        }
    } else {
        fn_8017BA60("Couldn't mount card: ", result);
    }

    fn_8017AF78();
    return 0;
}
