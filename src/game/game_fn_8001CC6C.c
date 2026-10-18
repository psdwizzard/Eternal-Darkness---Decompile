typedef int s32;

char lbl_8023CE18[] = "EDSetAllCinematicFlagsForFinishedAlignments";

extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void *fn_80201BC8();
extern void fn_8012B344(void*);
extern void fn_8011FBD0(void*, s32, s32);
extern void* lbl_8064C4E4;
extern char lbl_8023BEF8[];

s32 fn_8001CC6C(void* script)
{
    void* object;
    void* entry;
    s32 second;
    s32 first;

    if (lua_gettop(script) != 2) {
        luaO_verror(script, lbl_8023BEF8, 2, lua_gettop(script));
        return 0;
    }

    first = (s32)lua_tonumber(script, 1);
    second = (s32)lua_tonumber(script, 2);
    entry = fn_80201814(first);
    if (entry != 0) {
        object = fn_80201BC8(entry);
    } else {
        object = 0;
    }

    if (entry != 0 && object != 0) {
        fn_8012B344(lbl_8064C4E4);
        fn_8011FBD0(object, second, 1);
    }
    return 0;
}
