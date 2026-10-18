typedef struct Parser Parser;
typedef struct Entry Entry;

extern int subexpr(Parser*, Entry*, int);

int expr(Parser* parser, Entry* entry)
{
    return subexpr(parser, entry, -1);
}
