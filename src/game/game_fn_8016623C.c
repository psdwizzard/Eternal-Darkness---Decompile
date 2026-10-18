typedef struct Parser Parser;

extern void fn_80163DA4(Parser*);
extern int funcname(Parser*, int*);
extern void body(Parser*, int, int);
extern void luaK_storevar(Parser*, int*);

void funcstat(Parser* parser, int value)
{
    int output;
    int special;

    fn_80163DA4(parser);
    special = funcname(parser, &output);
    body(parser, special, value);
    luaK_storevar(parser, &output);
}
