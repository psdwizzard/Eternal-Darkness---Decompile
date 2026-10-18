typedef struct Parser {
    char padding_00[8];
    int token;
    char padding_0C[0x1C];
    void* state;
} Parser;

typedef struct Entry {
    int type;
    int value_04;
    int value_08;
} Entry;

extern void fn_80163DA4(Parser*);
extern void luaK_tostack(Parser*, Entry*, int);
extern int checkname(Parser*);
extern void luaK_kstr(Parser*, int);
extern void exp1(Parser*);
extern void check(Parser*, int);
extern void luaK_code1(void*, int, int);
extern void funcargs(Parser*, int);

void var_or_func_tail(Parser* parser, Entry* entry)
{
    int value;

    for (;;) {
        switch (parser->token) {
        case 0x2E:
            fn_80163DA4(parser);
            luaK_tostack(parser, entry, 1);
            luaK_kstr(parser, checkname(parser));
            entry->type = 2;
            break;
        case 0x5B:
            fn_80163DA4(parser);
            luaK_tostack(parser, entry, 1);
            entry->type = 2;
            exp1(parser);
            check(parser, 0x5D);
            break;
        case 0x3A:
            fn_80163DA4(parser);
            value = checkname(parser);
            luaK_tostack(parser, entry, 1);
            luaK_code1(parser->state, 0x10, value);
            funcargs(parser, 1);
            entry->type = 3;
            entry->value_08 = -1;
            entry->value_04 = -1;
            break;
        case 0x28:
        case 0x7B:
        case 0x11B:
            luaK_tostack(parser, entry, 1);
            funcargs(parser, 0);
            entry->type = 3;
            entry->value_08 = -1;
            entry->value_04 = -1;
            break;
        default:
            return;
        }
    }
}
