typedef int s32;

extern s32 lbl_8064D18C;
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void fn_800073D8(s32);

s32 fn_8001221C(void* script)
{
    s32 value;
    void* parser;

    parser = script;
    if (lua_gettop(parser) != 0) {
        value = (s32)lua_tonumber(parser, 1);
    } else {
        value = lbl_8064D18C;
    }
    fn_800073D8(value);
    return 0;
}
