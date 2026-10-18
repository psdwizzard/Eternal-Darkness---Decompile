typedef struct Frame {
    void* parent;
    int value;
    int index;
} Frame;

typedef struct Parser {
    char padding_00[0x1C];
    short index;
    char padding_1E[0x0A];
    void* state;
} Parser;

void enterbreak(Parser* parser, Frame* frame)
{
    frame->index = parser->index;
    frame->value = -1;
    frame->parent = parser->state;
    parser->state = frame;
}
