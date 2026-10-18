typedef struct RuntimeObject {
    char padding_00[0x18];
    int value_18;
    char padding_1C[4];
    short value_20;
    short value_22;
    short value_24;
    char padding_26[0x1A];
    int value_40;
} RuntimeObject;

typedef struct ParserState {
    RuntimeObject* object;
    struct ParserState* parent;
    struct Parser* parser;
    void* allocator;
    void* value_10;
    void* value_14;
    int value_18;
    short value_1C;
    short value_1E;
    short value_20;
    char padding_22[2];
    void* value_24;
    void* value_28;
} ParserState;

typedef struct Parser {
    char padding_00[0x28];
    ParserState* state;
    void* allocator;
    char padding_30[0x0C];
    int value_3C;
} Parser;

extern void* luaF_newproto(void*);

void open_func(Parser* parser, ParserState* state)
{
    RuntimeObject* object = luaF_newproto(parser->allocator);

    state->parent = parser->state;
    state->parser = parser;
    state->allocator = parser->allocator;
    parser->state = state;
    state->value_1C = 0;
    state->value_1E = 0;
    state->value_20 = 0;
    state->value_28 = 0;
    state->object = object;
    object->value_40 = parser->value_3C;
    state->value_10 = 0;
    state->value_14 = 0;
    state->value_24 = 0;
    state->value_18 = -1;
    object->value_18 = 0;
    object->value_24 = 0;
    object->value_20 = 0;
    object->value_22 = 0;
}
