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
extern void fn_8015F988(ParserState*, int);
extern int fn_8015EC10(ParserState*);
extern void* fn_8016B5CC(void*, void*, unsigned int, char*, int);
extern void fn_8016437C(Parser*, int);
extern void fn_80161244(void*, RuntimeObject*, int);

void fn_80164A64(Parser* parser)
{
    void* allocator = parser->allocator;
    ParserState* state = parser->state;
    RuntimeObject* object = state->object;

    fn_8015F988(state, 0);
    fn_8015EC10(state);
    object->values_18 = fn_8016B5CC(allocator, object->values_18,
                                    state->value_10 * 4, lbl_8024F8B0, 0x14D);
    object->values_08 = fn_8016B5CC(allocator, object->values_08,
                                    object->count_0C * 4, lbl_8024F8B0, 0x14E);
    object->values_00 = fn_8016B5CC(allocator, object->values_00,
                                    object->count_04 * 8, lbl_8024F8B0, 0x14F);
    object->values_10 = fn_8016B5CC(allocator, object->values_10,
                                    object->count_14 * 4, lbl_8024F8B0, 0x150);
    fn_8016437C(parser, state->value_1E);
    object->values_38 = fn_8016B5CC(allocator, object->values_38,
                                    object->count_34 * 12, lbl_8024F8B0, 0x152);
    object->values_2C = fn_8016B5CC(allocator, object->values_2C,
                                    (object->count_30 + 1) * 4,
                                    lbl_8024F8B0, 0x153);
    object->values_2C[object->count_30++] = 0x7FFFFFFD;
    fn_80161244(allocator, object, state->value_10);
    parser->state = state->parent;
}
