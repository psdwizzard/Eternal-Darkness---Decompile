extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void fn_801EF36C(int);
extern int lbl_8064D6EC;

int fn_8016D8A4(void* state)
{
    int value;

    switch (lua_gettop(state)) {
    case 2:
        fn_801EF36C((int)lua_tonumber(state, 2));
    case 1:
        value = (int)lua_tonumber(state, 1);
        break;
    }
    lbl_8064D6EC = value;
    return 0;
}
