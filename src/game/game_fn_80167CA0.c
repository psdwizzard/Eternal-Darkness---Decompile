typedef struct Parser {
    char pad0[0x48];
    void* rows;
    int max_row;
    char pad50[0x10];
    int nblocks;
} Parser;

#pragma use_lmw_stmw on

extern void* luaM_growaux(Parser*, void*, int, int, int, void*, int);
extern void init_entry(Parser*, int);
extern char lbl_8064BBC4;

void luaT_init(Parser* parser)
{
    int i;

    parser->rows = luaM_growaux(parser, parser->rows, 0, 6, 64,
                               &lbl_8064BBC4, 0x7FFFFFFD);
    parser->nblocks += 384;
    parser->max_row = 5;

    for (i = 0; i <= parser->max_row; i++) {
        init_entry(parser, i);
    }
}
