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
extern void block(Parser*);
extern void check_match(Parser*, int, int, Entry*);
extern void cond(Parser*, Entry*);
extern void luaK_patchlist(State*, int, int);
extern void leavebreak(State*, Entry*);

void repeatstat(Parser* parser, Entry* output)
{
    State* state = parser->state;
    int start = luaK_getlabel(state);
    Entry value;
    Entry saved;

    enterbreak(state, &saved);
    fn_80163DA4(parser);
    block(parser);
    check_match(parser, 0x111, 0x10E, output);
    cond(parser, &value);
    luaK_patchlist(state, value.extra, start);
    leavebreak(state, &saved);
}
