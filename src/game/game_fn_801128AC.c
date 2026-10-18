extern double lua_tonumber(void*, int);
extern void fn_80112614(int);

int fn_801128AC(void* object)
{
    fn_80112614((int)lua_tonumber(object, 1));
    return 0;
}
