typedef struct Parser Parser;
typedef struct Entry Entry;

extern void fn_80163DA4(Parser*);
extern void cond(Parser*, Entry*);
extern void check(Parser*, int);
extern void block(Parser*);

void test_then_block(Parser* parser, Entry* output)
{
    fn_80163DA4(parser);
    cond(parser, output);
    check(parser, 0x110);
    block(parser);
}
