typedef struct SearchResult {
    int found;
    int depth;
    int value;
} SearchResult;

typedef struct ParserState {
    char padding_00[4];
    void* parent;
} ParserState;

typedef struct Parser {
    char padding_00[0x28];
    ParserState* state;
} Parser;

extern char lbl_8024F848[];
extern char lbl_8024F868[];
extern int search_local(Parser*, void*, SearchResult*);
extern void luaX_syntaxerror(Parser*, char*, char*);
extern int string_constant(void*, void*);
extern int indexupvalue(Parser*, SearchResult*);
extern void luaK_code1(ParserState*, int, int);

void pushupvalue(Parser* parser, void* value)
{
    SearchResult result;
    ParserState* state = parser->state;
    int level = search_local(parser, value, &result);

    if (level == -1) {
        if (state->parent == 0) {
            luaX_syntaxerror(parser, lbl_8024F848, (char*)value + 0x14);
        }
        result.depth = string_constant(state->parent, value);
    } else if (level != 1) {
        luaX_syntaxerror(parser, lbl_8024F868, (char*)value + 0x14);
    }
    luaK_code1(state, 10, indexupvalue(parser, &result));
}
