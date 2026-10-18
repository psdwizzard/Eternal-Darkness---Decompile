typedef struct Parser {
    char pad0[0x28];
    void* state;
} Parser;

extern void var_or_func(Parser*, int*);
extern char* luaK_lastisopen(void*);
extern void check_condition(Parser*, char*, const char*);
extern void luaK_setcallreturns(void*, int);
extern int assignment(Parser*, int*, int);
extern void luaK_adjuststack(void*, int);
extern const char lbl_8024F99C[];

void namestat(Parser* parser)
{
    int value;
    void* state = parser->state;

    var_or_func(parser, &value);
    if (value == 3) {
        check_condition(parser, luaK_lastisopen(state), lbl_8024F99C);
        luaK_setcallreturns(state, 0);
    } else {
        int result = assignment(parser, &value, 1);
        luaK_adjuststack(state, result);
    }
}
