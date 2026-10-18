typedef struct ParserRow {
    void* values[15];
    void* extra;
} ParserRow;

typedef struct Parser {
    char pad0[0x48];
    ParserRow* volatile rows;
} Parser;

void init_entry(Parser* parser, int row)
{
    int i;

    for (i = 0; i < 15; i++) {
        parser->rows[row].values[i] = 0;
    }
    parser->rows[row].extra = 0;
}
