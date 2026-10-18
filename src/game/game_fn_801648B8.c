typedef struct Frame {
    void* parent;
    int value;
    int index;
} Frame;

typedef struct Parser {
    char padding_00[0x28];
    void* state;
} Parser;

extern int luaK_getlabel(Parser*);
extern void luaK_patchlist(Parser*, int, int);

void leavebreak(Parser* parser, Frame* frame)
{
    parser->state = frame->parent;
    luaK_patchlist(parser, frame->value, luaK_getlabel(parser));
}
