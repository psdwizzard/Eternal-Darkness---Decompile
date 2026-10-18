typedef struct Parser {
    char padding_00[8];
    int token;
} Parser;

typedef struct Entry {
    int type;
    int value_04;
    int value_08;
} Entry;

extern signed char priority[];
extern void luaK_prefix(Parser*, int, Entry*);
extern void luaK_infix(Parser*, int, Entry*);
extern void luaK_posfix(Parser*, int, Entry*, Entry*);
extern void fn_80163DA4(Parser*);
extern void simpleexp(Parser*, Entry*);
extern int getunopr(int);
extern int getbinopr(int);

int subexpr(Parser* parser, Entry* entry, int precedence)
{
    int operator_kind;
    signed char* operator_info;
    int value_kind = getunopr(parser->token);

    if (value_kind != 2) {
        fn_80163DA4(parser);
        subexpr(parser, entry, 7);
        luaK_prefix(parser, value_kind, entry);
    } else {
        simpleexp(parser, entry);
    }

    operator_kind = getbinopr(parser->token);
    while (operator_kind != 14 &&
           priority[operator_kind * 2] > precedence) {
        fn_80163DA4(parser);
        luaK_infix(parser, operator_kind, entry);
        operator_info = &priority[operator_kind * 2];
        {
            Entry right;
            int next_kind = subexpr(parser, &right, operator_info[1]);
            luaK_posfix(parser, operator_kind, entry, &right);
            operator_kind = next_kind;
        }
    }
    return operator_kind;
}
