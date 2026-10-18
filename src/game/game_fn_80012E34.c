typedef int s32;

extern const char lbl_8023BEF8[];
char lbl_8023CA98[] =
    "Invalid Alignment of %i\0"
    "( Error: pStartVert is NULL )\0\0\0"
    "( Error: pEndVert is NULL )";
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void fn_800355F0(void*, s32);
extern int fn_80201B44();
extern void fn_800427E0(s32);

s32 fn_80012E34(void* script)
{
    register s32 object_id;
    register s32 mode;
    register void* object;
    register void* parser = script;

    if (lua_gettop(parser) != 2) {
        luaO_verror(parser, lbl_8023BEF8, 2, lua_gettop(parser));
        return 0;
    }

    object_id = (s32)lua_tonumber(parser, 1);
    object = fn_80201814(object_id);
    if (object != 0) {
        mode = (s32)lua_tonumber(parser, 2);
        if (mode < 0 || mode > 4) {
            luaO_verror(parser, lbl_8023CA98, mode);
            return 0;
        }

        fn_800355F0(object, mode);
        if (fn_80201B44() == object_id) {
            fn_800427E0(mode);
        }
    }
    return 0;
}
