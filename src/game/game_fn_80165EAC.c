typedef struct State State;

typedef struct Parser {
    char padding_00[0x08];
    int token;
    char padding_0C[0x1C];
    State* state;
} Parser;

typedef struct Entry {
    int type;
    int value;
    int extra;
} Entry;

extern char lbl_8024F9BC[];
extern void enterbreak(State*, Entry*);
extern void fn_80163DA4(Parser*);
extern int str_checkname(Parser*);
extern void fornum(Parser*, int);
extern void forlist(Parser*, int);
extern void luaK_error(Parser*, char*);
extern void check_match(Parser*, int, int, Entry*);
extern void leavebreak(State*, Entry*);

void forstat(Parser* parser, Entry* output)
{
    State* state = parser->state;
    Entry saved;
    int expression;

    enterbreak(state, &saved);
    fn_80163DA4(parser);
    expression = str_checkname(parser);
    switch (parser->token) {
    case 0x3D:
        fornum(parser, expression);
        break;
    case 0x2C:
        forlist(parser, expression);
        break;
    default:
        luaK_error(parser, lbl_8024F9BC);
        break;
    }
    check_match(parser, 0x106, 0x107, output);
    leavebreak(state, &saved);
}
