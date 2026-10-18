typedef struct State State;

typedef struct Parser {
    char padding_00[8];
    int token;
    char padding_0C[0x1C];
    State* state;
} Parser;

typedef struct Entry {
    int type;
    int value_04;
    int value_08;
} Entry;

extern char lbl_8024F978[];
extern char lbl_8024F99C[];
extern void luaX_checklimit(Parser*, int, int, char*);
extern void fn_80163DA4(Parser*);
extern void var_or_func(Parser*, Entry*);
extern void check_condition(Parser*, int, char*);
extern void check(Parser*, int);
extern int explist1(Parser*);
extern void adjust_mult_assign(Parser*, int, int);
extern void luaK_storevar(Parser*, Entry*);
extern int luaK_code2(State*, int, int, int);

int assignment(Parser* parser, Entry* entry, int count)
{
    int left = 0;

    luaX_checklimit(parser, count, 254, lbl_8024F978);
    if (parser->token == ',') {
        Entry next;
        fn_80163DA4(parser);
        var_or_func(parser, &next);
        check_condition(parser, next.type != 3, lbl_8024F99C);
        left = assignment(parser, &next, count + 1);
    } else {
        int expressions;
        check(parser, '=');
        expressions = explist1(parser);
        adjust_mult_assign(parser, count, expressions);
    }

    if (entry->type != 2) {
        luaK_storevar(parser, entry);
    } else {
        luaK_code2(parser->state, 20, left + count + 2, 1);
        left += 2;
    }
    return left;
}
