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
    char padding_04[0x0C];
    void* value;
    char padding_14[0x0A];
    short depth;
    char padding_20[0x18C];
    int slots[1];
} ParserState;

typedef struct Parser {
    char padding_00[0x28];
    ParserState* state;
} Parser;

void removelocalvars(Parser* parser, int count)
{
    ParserState* state = parser->state;

    while (count--) {
        state->table->values[state->slots[--state->depth]].third = state->value;
    }
}
