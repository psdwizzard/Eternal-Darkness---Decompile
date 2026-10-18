typedef struct ParserState {
    char padding_00[0x1C];
    short value_1C;
} ParserState;

typedef struct Parser {
    char padding_00[8];
    int token;
    int value_0C;
    int value_10;
    char padding_14[0x14];
    ParserState* state;
    char padding_2C[8];
    int line;
} Parser;

extern char lbl_8024F8CC[];
extern void fn_80163DA4(Parser*);
extern int explist1(Parser*);
extern void check_match(Parser*, int, int, int);
extern void constructor(Parser*);
extern void code_string(Parser*, int);
extern void luaK_error(Parser*, char*);
extern void luaK_code2(ParserState*, int, int, int);

void funcargs(Parser* parser, int count)
{
    ParserState* state = parser->state;
    int new_count = state->value_1C - count - 1;
    int line;

    switch (parser->token) {
    case 0x28:
        line = parser->line;
        fn_80163DA4(parser);
        if (parser->token != 0x29) {
            explist1(parser);
        }
        check_match(parser, 0x29, 0x28, line);
        break;
    case 0x7B:
        constructor(parser);
        break;
    case 0x11B:
        code_string(parser, parser->value_10);
        fn_80163DA4(parser);
        break;
    default:
        luaK_error(parser, lbl_8024F8CC);
        break;
    }

    state->value_1C = new_count;
    luaK_code2(state, 2, new_count, 0xFF);
}
