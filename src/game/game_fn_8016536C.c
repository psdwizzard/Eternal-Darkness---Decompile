typedef struct ParseResult {
    int value;
    int kind;
} ParseResult;

typedef struct OutputData {
    char padding_00[0x18];
    unsigned int* words;
} OutputData;

typedef struct Parser {
    char padding_00[0x28];
    OutputData** output;
    char padding_2C[8];
    void* context;
} Parser;

extern char lbl_8024F924[];
extern char lbl_8024F940[];
extern int luaK_code1(OutputData**, int, int);
extern void check(Parser*, int);
extern void constructor_part(Parser*, ParseResult*);
extern int optional(Parser*, int);
extern void check_condition(Parser*, int, char*);
extern void check_match(Parser*, int, int, void*);
extern void luaX_checklimit(Parser*, int, int, char*);

void constructor(Parser* parser)
{
    OutputData** output = parser->output;
    void* context = parser->context;
    int index = luaK_code1(output, 0x11, 0);
    ParseResult first;
    ParseResult second;
    int count;

    check(parser, 0x7B);
    constructor_part(parser, &first);
    count = first.value;
    if (optional(parser, 0x3B)) {
        constructor_part(parser, &second);
        check_condition(parser, first.kind != second.kind, lbl_8024F924);
        count += second.value;
    }
    check_match(parser, 0x7D, 0x7B, context);
    luaX_checklimit(parser, count, 0x3FFFFFF, lbl_8024F940);
    (*output)->words[index] = ((*output)->words[index] & 0x3F) | (count << 6);
}
