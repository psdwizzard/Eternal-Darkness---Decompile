typedef struct Parser {
    char padding_00[0x08];
    int token;
} Parser;

extern int str_checkname(Parser*);
extern void singlevar(Parser*, int, int*);
extern void fn_80163DA4(Parser*);
extern void luaK_tostack(Parser*, int*, int);
extern int checkname(Parser*);
extern void luaK_kstr(Parser*, int);

int funcname(Parser* parser, int* output)
{
    int special = 0;

    singlevar(parser, str_checkname(parser), output);
    if (parser->token == 0x3A || parser->token == 0x2E) {
        special = parser->token == 0x3A;
        fn_80163DA4(parser);
        luaK_tostack(parser, output, 1);
        luaK_kstr(parser, checkname(parser));
        *output = 2;
    }
    return special;
}
