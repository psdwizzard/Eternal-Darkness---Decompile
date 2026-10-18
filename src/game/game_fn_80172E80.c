extern int lua_gettop(void*);
extern void luaO_verror(void*, const char*, ...);
extern void OSDumpHeap(void*);
extern void* __OSCurrHeap;
extern const char lbl_8024FF00[];

int fn_80172E80(void* state)
{
    if (lua_gettop(state) != 0) {
        luaO_verror(state, lbl_8024FF00, 0, lua_gettop(state));
        return 0;
    }

    OSDumpHeap(__OSCurrHeap);
    return 0;
}
