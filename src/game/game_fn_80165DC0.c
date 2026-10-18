typedef struct Parser {
    char padding_00[0x08];
    int token;
    char padding_0C[0x04];
    void* value;
    char padding_14[0x18];
    void* allocator;
} Parser;

extern char lbl_8024F9AC[];
extern char lbl_8064BB70;
extern char lbl_8064BB74;
extern void check(Parser*, int);
extern int str_checkname(Parser*);
extern void* luaS_new(void*, char*);
extern void check_condition(Parser*, int, char*);
extern void fn_80163DA4(Parser*);
extern void exp1(Parser*);
extern void new_localvarstr(Parser*, char*, int);
extern void new_localvar(Parser*, int, int);
extern void forbody(Parser*, int, int, int);

void forlist(Parser* parser, int output)
{
    int valid;
    int expression;

    check(parser, 0x2C);
    expression = str_checkname(parser);
    valid = 0;
    if (parser->token == 0x113 &&
        parser->value == luaS_new(parser->allocator, &lbl_8064BB70)) {
        valid = 1;
    }
    check_condition(parser, valid, lbl_8024F9AC);
    fn_80163DA4(parser);
    exp1(parser);
    new_localvarstr(parser, &lbl_8064BB74, 0);
    new_localvar(parser, output, 1);
    new_localvar(parser, expression, 2);
    forbody(parser, 3, 0x2E, 0x2F);
}
