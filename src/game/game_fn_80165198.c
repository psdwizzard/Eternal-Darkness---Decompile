typedef struct Parser {
    char padding_00[8];
    int token;
    char padding_0C[0x1C];
    void* output;
} Parser;

extern char lbl_8024F900[];
extern void exp1(Parser*);
extern void fn_80163DA4(Parser*);
extern void luaX_checklimit(Parser*, int, int, char*);
extern void luaK_code2(void*, int, int, int);

int listfields(Parser* parser)
{
    void* output = parser->output;
    int count = 1;

    exp1(parser);
    while (parser->token == 0x2C) {
        int page;

        fn_80163DA4(parser);
        if (parser->token == 0x3B || parser->token == 0x7D) {
            break;
        }
        exp1(parser);
        count++;
        page = count / 62;
        luaX_checklimit(parser, page, 0x1FFFF, lbl_8024F900);
        if (count % 62 == 0) {
            luaK_code2(output, 0x15, page - 1, 62);
        }
    }
    luaK_code2(output, 0x15, count / 62, count % 62);
    return count;
}
