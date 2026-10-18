typedef struct Parser {
    char padding_00[8];
    int token;
    char padding_0C[0xC];
    int lookahead;
} Parser;

typedef struct ParseResult {
    int value;
    int kind;
} ParseResult;

extern void fn_80163E08(Parser*);
extern int recfields(Parser*);
extern int listfields(Parser*);

void constructor_part(Parser* parser, ParseResult* result)
{
    switch (parser->token) {
    case 0x3B:
    case 0x7D:
        result->value = 0;
        result->kind = parser->token;
        break;
    case 0x113:
        fn_80163E08(parser);
        if (parser->lookahead != 0x3D) {
            goto parse_general;
        }
    case 0x5B:
        result->value = recfields(parser);
        result->kind = 1;
        break;
    default:
    parse_general:
        result->value = listfields(parser);
        result->kind = 0;
        break;
    }
}
