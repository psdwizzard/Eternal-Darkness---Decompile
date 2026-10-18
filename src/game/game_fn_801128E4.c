extern int lbl_8064CD6C;

extern void lua_pushnumber(void*, double);

int fn_801128E4(void* object)
{
    lua_pushnumber(object, (double)lbl_8064CD6C);
    return 1;
}
