typedef struct OuterObject {
    char pad0[0x28];
    void* object;
} OuterObject;

extern void luaK_goiftrue(void*, void*, int);
extern void luaK_goiffalse(void*, void*, int);
extern void luaK_tostack(OuterObject*, void*, int);

void luaK_infix(OuterObject* outer, int type, void* command)
{
    void* object = outer->object;

    switch (type) {
    case 12:
        luaK_goiftrue(object, command, 1);
        break;
    case 13:
        luaK_goiffalse(object, command, 1);
        break;
    default:
        luaK_tostack(outer, command, 1);
        break;
    }
}
