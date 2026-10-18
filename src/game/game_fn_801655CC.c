typedef struct Parser Parser;

typedef struct Entry {
    int type;
    int value_04;
    int value_08;
} Entry;

extern void luaK_tostack(Parser*, Entry*, int);
extern void expr(Parser*, Entry*);

void exp1(Parser* parser)
{
    Entry entry;
    expr(parser, &entry);
    luaK_tostack(parser, &entry, 1);
}
