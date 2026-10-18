typedef struct Parser {
    char padding_00[0x28];
    void* table;
} Parser;

extern void* str_checkname(Parser*);
extern int string_constant(void*, void*);

void checkname(Parser* parser)
{
    string_constant(parser->table, str_checkname(parser));
}
