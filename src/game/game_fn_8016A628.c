extern char lbl_8024FE60[];
extern void* luaO_typenames[];

void* lua_typename(void* context, int index)
{
    if (index == -1) {
        return lbl_8024FE60;
    }
    return luaO_typenames[index];
}
