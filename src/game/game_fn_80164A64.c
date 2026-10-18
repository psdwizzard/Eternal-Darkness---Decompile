typedef struct RuntimeObject {
    void* values_00;
    int count_04;
    void* values_08;
    int count_0C;
    void* values_10;
    int count_14;
    void* values_18;
    char padding_1C[0x10];
    int* values_2C;
    int count_30;
    int count_34;
    void* values_38;
} RuntimeObject;

typedef struct ParserState {
    RuntimeObject* object;
    struct ParserState* parent;
    char padding_08[8];
    int value_10;
    char padding_14[0xA];
    short value_1E;
} ParserState;

typedef struct Parser {
    char padding_00[0x28];
    ParserState* state;
    void* allocator;
} Parser;

extern char lbl_8024F8B0[];
extern void luaK_code0(ParserState*, int);
extern int luaK_getlabel(ParserState*);
extern void* luaM_realloc(void*, void*, unsigned int, char*, int);
extern void removelocalvars(Parser*, int);
extern void luaF_protook(void*, RuntimeObject*, int);

void close_func(Parser* parser)
{
    void* allocator = parser->allocator;
    ParserState* state = parser->state;
    RuntimeObject* object = state->object;

    luaK_code0(state, 0);
    luaK_getlabel(state);
    object->values_18 = luaM_realloc(allocator, object->values_18,
                                    state->value_10 * 4, lbl_8024F8B0, 0x14D);
    object->values_08 = luaM_realloc(allocator, object->values_08,
                                    object->count_0C * 4, lbl_8024F8B0, 0x14E);
    object->values_00 = luaM_realloc(allocator, object->values_00,
                                    object->count_04 * 8, lbl_8024F8B0, 0x14F);
    object->values_10 = luaM_realloc(allocator, object->values_10,
                                    object->count_14 * 4, lbl_8024F8B0, 0x150);
    removelocalvars(parser, state->value_1E);
    object->values_38 = luaM_realloc(allocator, object->values_38,
                                    object->count_34 * 12, lbl_8024F8B0, 0x152);
    object->values_2C = luaM_realloc(allocator, object->values_2C,
                                    (object->count_30 + 1) * 4,
                                    lbl_8024F8B0, 0x153);
    object->values_2C[object->count_30++] = 0x7FFFFFFD;
    luaF_protook(allocator, object, state->value_10);
    parser->state = state->parent;
}
