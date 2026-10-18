typedef struct Parser {
    char pad0[8];
    int token;
} Parser;

extern void fn_80163DA4(Parser*);
extern int str_checkname(Parser*);
extern void new_localvar(Parser*, int, int);
extern void luaK_error(Parser*, const char*);
extern int optional(Parser*, int);
extern void code_params(Parser*, int, int);
extern const char lbl_8024F9FC[];

void parlist(Parser* parser)
{
    int count = 0;
    int terminal = 0;

    if (parser->token != 0x29) {
        do {
            switch (parser->token) {
            case 0x115:
                fn_80163DA4(parser);
                terminal = 1;
                break;
            case 0x113:
                new_localvar(parser, str_checkname(parser), count++);
                break;
            default:
                luaK_error(parser, lbl_8024F9FC);
                break;
            }
        } while (!terminal && optional(parser, 0x2C));
    }
    code_params(parser, count, terminal);
}
