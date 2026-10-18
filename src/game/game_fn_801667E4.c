typedef struct Parser {
    char pad0[0x44];
    void* value44;
} Parser;

extern void* luaH_new(Parser*, int);
extern void luaD_init(Parser*, int);
extern void luaS_init(Parser*);
extern void luaX_init(Parser*);
extern void luaT_init(Parser*);
extern void lua_newtable(Parser*);
extern void lua_ref(Parser*, int);
extern int errormessage(void*);
extern void lua_pushcclosure(Parser*, int (*)(void*), int);
extern void lua_setglobal(Parser*, const char*);
extern const char lbl_8024FA18[];

void f_luaopen(Parser* parser, int* configured_size)
{
    int size = 0x400;

    if (*configured_size != 0) {
        size = *configured_size + 0x14;
    }
    parser->value44 = luaH_new(parser, 10);
    luaD_init(parser, size);
    luaS_init(parser);
    luaX_init(parser);
    luaT_init(parser);
    lua_newtable(parser);
    lua_ref(parser, 1);
    lua_pushcclosure(parser, errormessage, 0);
    lua_setglobal(parser, lbl_8024FA18);
}
