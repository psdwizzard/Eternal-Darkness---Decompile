typedef int s32;
typedef unsigned char u8;

extern const char lbl_8023BEF8[];
extern char lbl_8030206C[];
extern void fn_8014CBC0(char*);
extern int lua_gettop(void*);
extern double lua_tonumber(void*, int);
extern void luaO_verror(void*, const char*, ...);
extern void *fn_80201814();
extern void* fn_80201C24();
extern void fn_80157B60(void*, u8);
extern void fn_80157B3C(void*, s32);
extern char* fn_80047D6C(void);
extern int fn_80201B44();
extern void fn_800DBF60(s32, void*, s32, char*, float);

s32 fn_800133CC(void* script)
{
    s32 first;
    s32 second;
    s32 kind;
    void* parser = script;
    void* object;
    float amount;
    s32 use_name;
    s32 mode;
    void* context;
    char* name;

    fn_8014CBC0(lbl_8030206C);
    if (lua_gettop(parser) != 5) {
        luaO_verror(parser, lbl_8023BEF8, 5, lua_gettop(parser));
        return 0;
    }

    first = (s32)lua_tonumber(parser, 1);
    second = (s32)lua_tonumber(parser, 2);
    kind = (s32)lua_tonumber(parser, 3);
    amount = (float)lua_tonumber(parser, 4);
    use_name = (s32)lua_tonumber(parser, 5);

    object = fn_80201814(first);
    if (object != 0) {
        context = fn_80201C24();
        fn_80157B60(context, (u8)second);

        switch (kind) {
        case 0x10000:
            mode = 2;
            break;
        case 0x20000:
            mode = 3;
            break;
        case 0x40000:
            mode = 4;
            break;
        }

        fn_80157B3C(context, mode);
        if (use_name != 0) {
            name = fn_80047D6C();
        } else {
            name = lbl_8030206C;
        }
        fn_800DBF60(fn_80201B44(), object, mode, name, amount);
    }
    return 0;
}
