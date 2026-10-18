typedef struct Parser {
    char padding_00[8];
    int token;
    char padding_0C[0x1C];
    void* output;
} Parser;

extern void recfield(Parser*);
extern void fn_80163DA4(Parser*);
extern void luaK_code1(void*, int, int);

int recfields(Parser* parser)
{
    int count = 1;
    void* output = parser->output;

    recfield(parser);
    while (parser->token == 0x2C) {
        fn_80163DA4(parser);
        if (parser->token == 0x3B || parser->token == 0x7D) {
            break;
        }
        recfield(parser);
        count++;
        if (count % 31 == 0) {
            luaK_code1(output, 0x16, 31);
        }
    }
    luaK_code1(output, 0x16, count % 31);
    return count;
}
