typedef struct Parser {
    char padding_00[8];
    int token;
    char padding_0C[4];
    double number;
    char padding_18[0x10];
    void* output;
    char padding_2C[8];
    void* context;
} Parser;

typedef struct Entry {
    int type;
    int value_04;
    int value_08;
} Entry;

extern char lbl_8024F960[];
extern void luaK_error(Parser*, char*);
extern void luaK_number(void*, double);
extern void luaK_adjuststack(void*, int);
extern void fn_80163DA4(Parser*);
extern void check(Parser*, int);
extern void code_string(Parser*, int);
extern void constructor(Parser*);
extern void var_or_func(Parser*, Entry*);
extern void expr(Parser*, Entry*);
extern void body(Parser*, int, void*);

void simpleexp(Parser* parser, Entry* entry)
{
    void* output = parser->output;

    switch (parser->token) {
    case 0x11A:
        {
            double number = parser->number;
            fn_80163DA4(parser);
            luaK_number(output, number);
        }
        break;
    case 0x11B:
        code_string(parser, *(int*)&parser->number);
        fn_80163DA4(parser);
        break;
    case 0x10B:
        luaK_adjuststack(output, -1);
        fn_80163DA4(parser);
        break;
    case 0x7B:
        constructor(parser);
        break;
    case 0x108:
        fn_80163DA4(parser);
        body(parser, 0, parser->context);
        break;
    case 0x28:
        fn_80163DA4(parser);
        expr(parser, entry);
        check(parser, 0x29);
        return;
    case 0x25:
    case 0x113:
        var_or_func(parser, entry);
        return;
    default:
        luaK_error(parser, lbl_8024F960);
        return;
    }

    entry->type = 3;
    entry->value_08 = -1;
    entry->value_04 = -1;
}
