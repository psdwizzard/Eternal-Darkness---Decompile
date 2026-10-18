typedef struct Parser {
    char padding_00[0x28];
    void* state;
} Parser;

extern int luaK_lastisopen(void*);
extern void luaK_setcallreturns(void*, int);
extern void luaK_adjuststack(void*, int);

void adjust_mult_assign(Parser* parser, int start, int end)
{
    void* state = parser->state;
    int count = end - start;

    if (end > 0 && luaK_lastisopen(state)) {
        count--;
        if (count <= 0) {
            luaK_setcallreturns(state, -count);
            count = 0;
        } else {
            luaK_setcallreturns(state, 0);
        }
    }
    luaK_adjuststack(state, count);
}
