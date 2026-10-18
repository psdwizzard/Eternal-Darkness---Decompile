typedef struct Parser {
    char padding_00[8];
    int token;
} Parser;

typedef struct Entry {
    int values[3];
} Entry;

extern void expr(Parser*, Entry*);
extern void luaK_tostack(Parser*, Entry*, int);
extern void fn_80163DA4(Parser*);

int explist1(Parser* parser)
{
    Entry entry;
    int count = 1;

    expr(parser, &entry);
    while (parser->token == 0x2C) {
        luaK_tostack(parser, &entry, 1);
        fn_80163DA4(parser);
        expr(parser, &entry);
        count++;
    }
    luaK_tostack(parser, &entry, 0);
    return count;
}
