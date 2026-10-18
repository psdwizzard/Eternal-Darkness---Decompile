typedef struct ValueTable {
    char padding_00[0x34];
    int count;
    void* values;
} ValueTable;

typedef struct TableHandle {
    ValueTable* table;
} TableHandle;

typedef struct Parser {
    char padding_00[0x28];
    TableHandle* handle;
    void* allocator;
} Parser;

extern char lbl_8064BB58;
extern void* luaM_growaux(void*, void*, unsigned int, unsigned int,
                         unsigned int, char*, unsigned int);

int luaI_registerlocalvar(Parser* parser, void* value)
{
    ValueTable* table = parser->handle->table;

    table->values = luaM_growaux(parser->allocator, table->values,
                                table->count, 1, 12, &lbl_8064BB58,
                                0x7FFFFFFD);
    ((void**)table->values)[table->count * 3] = value;
    return table->count++;
}
