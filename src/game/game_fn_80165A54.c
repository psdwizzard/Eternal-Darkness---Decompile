typedef struct State State;

typedef struct Parser {
    char padding_00[0x28];
    State* state;
} Parser;

typedef struct Entry Entry;

extern int expr(Parser*, Entry*);
extern void luaK_goiftrue(State*, Entry*, int);

void cond(Parser* parser, Entry* entry)
{
    expr(parser, entry);
    luaK_goiftrue(parser->state, entry, 0);
}
