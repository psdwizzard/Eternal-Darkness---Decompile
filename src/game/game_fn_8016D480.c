extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void fn_8020104C(int, void*, void*, int, float);
extern const char lbl_8024FF54[];

#pragma opt_propagation off
int fn_8016D480(void* state)
{
    int count;
    int x;
    void* context;
    unsigned int flags;
    int y;
    float z;

    context = state;
    count = lua_gettop(context);
    flags = 0;
    switch (count) {
    case 4:
        flags = (int)lua_tonumber(context, 4);
    case 3:
        x = (int)lua_tonumber(context, 1);
        y = (int)lua_tonumber(context, 2);
        z = (float)lua_tonumber(context, 3);
        break;
    default:
        luaO_verror(context, lbl_8024FF54, count);
        return 0;
    }
    if (x != 0) {
        fn_8020104C(y, 0, (void*)x, flags, z);
    }
    return 0;
}
#pragma opt_propagation reset
