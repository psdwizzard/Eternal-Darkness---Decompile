typedef struct SearchResult {
    int found;
    int depth;
} SearchResult;

typedef struct Parser {
    char padding_00[0x28];
    void* state;
} Parser;

extern char lbl_8024F814[];
extern int search_local(Parser*, void*, SearchResult*);
extern void luaX_syntaxerror(Parser*, char*, char*);
extern int string_constant(void*, void*);

void singlevar(Parser* parser, void* value, SearchResult* result)
{
    int level = search_local(parser, value, result);

    if (level >= 1) {
        luaX_syntaxerror(parser, lbl_8024F814, (char*)value + 0x14);
    } else if (level == -1) {
        result->depth = string_constant(parser->state, value);
    }
}
