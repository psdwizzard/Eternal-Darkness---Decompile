typedef struct State State;

typedef struct Parser {
    char padding_00[0x28];
    State* state;
} Parser;

typedef struct Entry {
    int type;
    int value;
    int extra;
} Entry;

extern int luaK_getlabel(State*);
extern void enterbreak(State*, Entry*);
extern void fn_80163DA4(Parser*);
extern void cond(Parser*, Entry*);
extern void check(Parser*, int);
extern void block(Parser*);
extern int luaK_jump(State*);
extern void luaK_patchlist(State*, int, int);
extern void check_match(Parser*, int, int, Entry*);
extern void leavebreak(State*, Entry*);

void whilestat(Parser* parser, Entry* output)
{
    State* state = parser->state;
    int start = luaK_getlabel(state);
    Entry value;
    Entry saved;

    enterbreak(state, &saved);
    fn_80163DA4(parser);
    cond(parser, &value);
    check(parser, 0x103);
    block(parser);
    luaK_patchlist(state, luaK_jump(state), start);
    luaK_patchlist(state, value.extra, luaK_getlabel(state));
    check_match(parser, 0x106, 0x112, output);
    leavebreak(state, &saved);
}
