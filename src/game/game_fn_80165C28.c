typedef struct State State;

typedef struct Parser {
    char padding_00[0x28];
    State* state;
} Parser;

typedef struct Entry Entry;

extern int luaK_code1(State*, int, int);
extern int luaK_getlabel(State*);
extern void check(Parser*, int);
extern void adjustlocalvars(Parser*, Entry*);
extern void block(Parser*);
extern void luaK_patchlist(State*, int, int);
extern void removelocalvars(Parser*, Entry*);

void forbody(Parser* parser, Entry* output, int left, int right)
{
    State* state = parser->state;
    int first = luaK_code1(state, left, -1);
    int start = luaK_getlabel(state);

    check(parser, 0x103);
    adjustlocalvars(parser, output);
    block(parser);
    luaK_patchlist(state, luaK_code1(state, right, -1), start);
    luaK_patchlist(state, first, luaK_getlabel(state));
    removelocalvars(parser, output);
}
