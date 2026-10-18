typedef int s32;
typedef unsigned short u16;

extern const char lbl_8023BEF8[];
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern s32 fn_800360B0(void*, u16*);
extern s32 fn_80036060(void*, u16);

s32 fn_80012008(void* script)
{
    s32 handle;
    void* entry;
    s32 mode;
    s32 bits;
    s32 new_flags;
    void* parser;
    u16 flags;

    parser = script;
    if (lua_gettop(parser) != 3) {
        luaO_verror(parser, lbl_8023BEF8, 3, lua_gettop(parser));
        return 0;
    }

    handle = (s32)lua_tonumber(parser, 1);
    mode = (s32)lua_tonumber(parser, 2);
    bits = (s32)lua_tonumber(parser, 3);
    entry = fn_80201814(handle);
    if (entry != 0) {
        flags = 0;
        if (fn_800360B0(entry, &flags) != 0) {
            if (mode == 0) {
                new_flags = flags | (u16)bits;
            } else {
                new_flags = flags & ~(u16)bits;
            }
            flags = new_flags;
            fn_80036060(entry, flags);
        }
    }
    return 0;
}
