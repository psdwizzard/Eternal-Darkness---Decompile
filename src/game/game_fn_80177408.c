extern void luaL_openlib(void*, const void*, int);
extern const char lbl_8023A994[];

void fn_80177408(void* state)
{
    luaL_openlib(state, lbl_8023A994, 0xD0);
}
