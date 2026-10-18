typedef struct RuntimeObject {
    char pad0[0x3C];
    void* context;
} RuntimeObject;

typedef struct ParserState {
    RuntimeObject* object;
    char pad4[0x28];
    char entries[99][12];
} ParserState;

typedef struct Parser Parser;

extern void open_func(Parser*, ParserState*);
extern void check(Parser*, int);
extern void new_localvarstr(Parser*, void*, int);
extern void adjustlocalvars(Parser*, int);
extern void parlist(Parser*);
extern void chunk(Parser*);
extern void check_match(Parser*, int, int, void*);
extern void close_func(Parser*);
extern void pushclosure(Parser*, ParserState*);
extern char lbl_8064BB7C;

void body(Parser* parser, int scoped, void* context)
{
    ParserState state;

    open_func(parser, &state);
    state.object->context = context;
    check(parser, 0x28);
    if (scoped) {
        new_localvarstr(parser, &lbl_8064BB7C, 0);
        adjustlocalvars(parser, 1);
    }
    parlist(parser);
    check(parser, 0x29);
    chunk(parser);
    check_match(parser, 0x106, 0x108, context);
    close_func(parser);
    pushclosure(parser, &state);
}
