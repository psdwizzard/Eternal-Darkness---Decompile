typedef struct Parser {
    char padding_00[0x08];
    int token;
} Parser;

extern void fn_80163DA4(Parser*);
extern int str_checkname(Parser*);
extern void new_localvar(Parser*, int, int);
extern int optional(Parser*, int);
extern int explist1(Parser*);
extern void adjust_mult_assign(Parser*, int, int);
extern void adjustlocalvars(Parser*, int);

void localstat(Parser* parser)
{
    int count = 0;
    int value;

    do {
        fn_80163DA4(parser);
        new_localvar(parser, str_checkname(parser), count++);
    } while (parser->token == 0x2C);
    if (optional(parser, 0x3D)) {
        value = explist1(parser);
    } else {
        value = 0;
    }
    adjust_mult_assign(parser, count, value);
    adjustlocalvars(parser, count);
}
