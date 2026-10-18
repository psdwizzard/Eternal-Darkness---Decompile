typedef struct State State;

typedef struct Parser {
    char padding_00[0x28];
    State* state;
} Parser;

extern char lbl_8064BB60;
extern char lbl_8064BB68;
extern void check(Parser*, int);
extern void exp1(Parser*);
extern int optional(Parser*, int);
extern int luaK_code1(State*, int, int);
extern void new_localvar(Parser*, int, int);
extern void new_localvarstr(Parser*, char*, int);
extern void forbody(Parser*, int, int, int);

void fornum(Parser* parser, int output)
{
    State* state = parser->state;

    check(parser, 0x3D);
    exp1(parser);
    check(parser, 0x2C);
    exp1(parser);
    if (optional(parser, 0x2C)) {
        exp1(parser);
    } else {
        luaK_code1(state, 6, 1);
    }
    new_localvar(parser, output, 0);
    new_localvarstr(parser, &lbl_8064BB60, 1);
    new_localvarstr(parser, &lbl_8064BB68, 2);
    forbody(parser, 3, 0x2C, 0x2D);
}
