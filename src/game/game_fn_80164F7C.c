typedef struct Parser Parser;

typedef struct Entry {
    int type;
    int value_04;
    int value_08;
} Entry;

extern int optional(Parser*, int);
extern int str_checkname(Parser*);
extern void pushupvalue(Parser*, int);
extern void singlevar(Parser*, int, Entry*);
extern void var_or_func_tail(Parser*, Entry*);

void var_or_func(Parser* parser, Entry* entry)
{
    if (optional(parser, 0x25)) {
        pushupvalue(parser, str_checkname(parser));
        entry->type = 3;
        entry->value_08 = -1;
        entry->value_04 = -1;
    } else {
        singlevar(parser, str_checkname(parser), entry);
    }
    var_or_func_tail(parser, entry);
}
