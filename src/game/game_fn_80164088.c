typedef struct Parser {
    char padding_00[0x28];
    void* table;
} Parser;

extern int string_constant(void*, void*);
extern void luaK_kstr(Parser*, int);

void code_string(Parser* parser, void* entry)
{
    luaK_kstr(parser, string_constant(parser->table, entry));
}
