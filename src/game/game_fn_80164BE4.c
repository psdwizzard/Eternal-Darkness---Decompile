typedef struct Parser {
    char padding_00[8];
    int token;
    char padding_0C[0x34];
} Parser;

typedef struct ParserState {
    void* object;
    char padding_04[0x4CC];
} ParserState;

typedef struct Input {
    char padding_00[0x10];
    void* source;
} Input;

extern char lbl_8024F8BC[];
extern void* luaS_new(Parser*, void*);
extern void luaX_setinput(Parser*, Parser*, Input*, void*);
extern void open_func(Parser*, ParserState*);
extern void fn_80163DA4(Parser*);
extern void chunk(Parser*);
extern void check_condition(Parser*, int, char*);
extern void close_func(Parser*);

void* luaY_parser(Parser* parser, Input* input)
{
    Parser local;
    ParserState state;
    luaX_setinput(parser, &local, input, luaS_new(parser, input->source));
    open_func(&local, &state);
    fn_80163DA4(&local);
    chunk(&local);
    check_condition(&local, local.token == 0x11C, lbl_8024F8BC);
    close_func(&local);
    return state.object;
}
