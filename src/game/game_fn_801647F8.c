typedef struct ValueTable {
    char padding_00[0x20];
    short depth;
    short flag;
} ValueTable;

typedef struct ParserState {
    ValueTable* table;
    char padding_04[0x1A];
    short depth;
} ParserState;

typedef struct Parser {
    char padding_00[0x28];
    ParserState* state;
} Parser;

extern char lbl_8024F8A4[];
extern char lbl_8064BB5C;
extern void adjustlocalvars(Parser*, int);
extern void luaX_checklimit(Parser*, int, int, char*);
extern void new_localvarstr(Parser*, char*, int);
extern void luaK_deltastack(ParserState*, int);

void code_params(Parser* parser, int count, int flag)
{
    ParserState* state = parser->state;

    adjustlocalvars(parser, count);
    luaX_checklimit(parser, state->depth, 100, lbl_8024F8A4);
    state->table->depth = state->depth;
    state->table->flag = flag;
    if (flag != 0) {
        new_localvarstr(parser, &lbl_8064BB5C, 0);
        adjustlocalvars(parser, 1);
    }
    luaK_deltastack(state, state->depth);
}
