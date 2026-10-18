typedef struct Parser {
    char pad0[8];
    int token;
    char padC[0x28];
    void* context;
} Parser;

extern void ifstat(Parser*, void*);
extern void whilestat(Parser*, void*);
extern void fn_80163DA4(Parser*);
extern void block(Parser*);
extern void check_match(Parser*, int, int, void*);
extern void forstat(Parser*, void*);
extern void repeatstat(Parser*, void*);
extern void funcstat(Parser*, void*);
extern void localstat(Parser*);
extern void namestat(Parser*);
extern void retstat(Parser*);
extern void breakstat(Parser*);
extern void luaK_error(Parser*, const char*);
extern const char lbl_8024F9E4[];

int stat(Parser* parser)
{
    void* context = parser->context;

    switch (parser->token) {
    case 0x109:
        ifstat(parser, context);
        return 0;
    case 0x112:
        whilestat(parser, context);
        return 0;
    case 0x103:
        fn_80163DA4(parser);
        block(parser);
        check_match(parser, 0x106, 0x103, context);
        return 0;
    case 0x107:
        forstat(parser, context);
        return 0;
    case 0x10E:
        repeatstat(parser, context);
        return 0;
    case 0x108:
        funcstat(parser, context);
        return 0;
    case 0x10A:
        localstat(parser);
        return 0;
    case 0x25:
    case 0x113:
        namestat(parser);
        return 0;
    case 0x10F:
        retstat(parser);
        return 1;
    case 0x102:
        breakstat(parser);
        return 1;
    default:
        luaK_error(parser, lbl_8024F9E4);
        return 0;
    }
}
