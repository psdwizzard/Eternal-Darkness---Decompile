typedef struct Parser {
    char padding_00[8];
    int token;
} Parser;

extern char lbl_8024F8E8[];
extern int checkname(Parser*);
extern void luaK_kstr(Parser*, int);
extern void fn_80163DA4(Parser*);
extern void exp1(Parser*);
extern void check(Parser*, int);
extern void luaK_error(Parser*, char*);

void recfield(Parser* parser)
{
    switch (parser->token) {
    case 0x113:
        luaK_kstr(parser, checkname(parser));
        break;
    case 0x5B:
        fn_80163DA4(parser);
        exp1(parser);
        check(parser, 0x5D);
        break;
    default:
        luaK_error(parser, lbl_8024F8E8);
        break;
    }
    check(parser, 0x3D);
    exp1(parser);
}
