extern unsigned int lbl_80331748[];

extern double lua_tonumber(void*, int);
extern unsigned int fn_800F5C54(double);
extern void lua_pushnumber(void*, double);
extern void lua_pushnil(void*);

int fn_801126E0(void* object)
{
    unsigned int value = fn_800F5C54(lua_tonumber(object, 1));

    value &= lbl_80331748[0];

    if (value != 0) {
        lua_pushnumber(object, (double)value);
    } else {
        lua_pushnil(object);
    }
    return 1;
}
