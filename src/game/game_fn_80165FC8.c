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

extern void test_then_block(Parser*, Entry*);
extern int luaK_jump(State*);
extern void luaK_concat(State*, int*, int);
extern int luaK_getlabel(State*);
extern void luaK_patchlist(State*, int, int);
extern void fn_80163DA4(Parser*);
extern void block(Parser*);
extern void check_match(Parser*, int, int, Entry*);

void ifstat(Parser* parser, Entry* output)
{
    State* state = parser->state;
    int start = -1;
    Entry entry;

    test_then_block(parser, &entry);
    while (parser->token == 0x105) {
        luaK_concat(state, &start, luaK_jump(state));
        luaK_patchlist(state, entry.extra, luaK_getlabel(state));
        test_then_block(parser, &entry);
    }
    if (parser->token == 0x104) {
        luaK_concat(state, &start, luaK_jump(state));
        luaK_patchlist(state, entry.extra, luaK_getlabel(state));
        fn_80163DA4(parser);
        block(parser);
    } else {
        luaK_concat(state, &start, entry.extra);
    }
    luaK_patchlist(state, start, luaK_getlabel(state));
    check_match(parser, 0x106, 0x109, output);
}
