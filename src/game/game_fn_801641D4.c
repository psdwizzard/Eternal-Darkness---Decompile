typedef struct ParserState {
    char padding_00[0x1E];
    short depth;
    char padding_20[0x18C];
    int slots[1];
} ParserState;

typedef struct Parser {
    char padding_00[0x28];
    ParserState* state;
} Parser;

extern char lbl_8024F804[];
extern void luaX_checklimit(Parser*, int, int, char*);
extern int luaI_registerlocalvar(Parser*, void*);

void new_localvar(Parser* parser, void* value, int count)
{
    ParserState* state = parser->state;

    luaX_checklimit(parser, state->depth + count + 1, 200, lbl_8024F804);
    state->slots[state->depth + count] = luaI_registerlocalvar(parser, value);
}
