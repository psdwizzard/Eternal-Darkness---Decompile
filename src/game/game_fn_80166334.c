typedef struct State {
    char pad0[0x1C];
    short previous;
    short current;
} State;

typedef struct Parser {
    char pad0[8];
    void* token;
    char padC[0x1C];
    State* state;
} Parser;

extern void fn_80163DA4(Parser*);
extern int block_follow(void*);
extern int explist1(Parser*);
extern void luaK_code1(State*, int, int);

void retstat(Parser* parser)
{
    State* state = parser->state;

    fn_80163DA4(parser);
    if (!block_follow(parser->token)) {
        explist1(parser);
    }
    luaK_code1(state, 1, parser->state->current);
    state->previous = state->current;
}
