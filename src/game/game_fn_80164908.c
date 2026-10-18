typedef struct Entry {
    int first;
    int second;
    int third;
} Entry;

typedef struct ValueTable {
    char padding_00[0x10];
    void** values;
    int count;
} ValueTable;

typedef struct ParserState {
    ValueTable* table;
    char padding_04[0x1C];
    short entry_count;
    char padding_22[0x0A];
    Entry entries[1];
} ParserState;

typedef struct Parser {
    char padding_00[0x28];
    ParserState* state;
    void* allocator;
} Parser;

extern char lbl_8024F7DC[];
extern void luaK_tostack(Parser*, Entry*, int);
extern void* luaM_growaux(void*, void*, unsigned int, unsigned int,
                         unsigned int, char*, unsigned int);
extern void luaK_code2(ParserState*, int, int, int);

void pushclosure(Parser* parser, ParserState* source)
{
    ParserState* state = parser->state;
    ValueTable* table = state->table;
    int i;

    for (i = 0; i < source->entry_count; i++) {
        luaK_tostack(parser, &source->entries[i], 1);
    }

    table->values = luaM_growaux(parser->allocator, table->values,
                                table->count, 1, 4, lbl_8024F7DC,
                                0x1FFFF);
    table->values[table->count++] = source->table;
    luaK_code2(state, 48, table->count - 1, source->entry_count);
}
