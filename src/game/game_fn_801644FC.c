typedef struct Value {
    void* first;
    void* second;
    void* third;
} Value;

typedef struct ValueTable {
    char padding_00[0x38];
    Value* values;
} ValueTable;

typedef struct ParserState {
    ValueTable* table;
    struct ParserState* parent;
    char padding_08[0x16];
    short depth;
    char padding_20[0x18C];
    int slots[1];
} ParserState;

typedef struct Parser {
    char padding_00[0x28];
    ParserState* state;
} Parser;

typedef struct SearchResult {
    int found;
    int depth;
} SearchResult;

int search_local(Parser* parser, void* value, SearchResult* result)
{
    ParserState* state = parser->state;
    int level = 0;

    while (state != 0) {
        int i;
        for (i = state->depth - 1; i >= 0; i--) {
            if (value == state->table->values[state->slots[i]].first) {
                result->found = 1;
                result->depth = i;
                return level;
            }
        }
        state = state->parent;
        level++;
    }
    result->found = 0;
    return -1;
}
