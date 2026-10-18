typedef struct Node {
    char pad0[4];
    int value;
    int position;
} Node;

typedef struct State {
    char pad0[0x1C];
    short position;
    char pad1E[10];
    Node* node;
} State;

typedef struct Parser {
    char pad0[0x28];
    State* state;
} Parser;

extern void luaK_error(Parser*, const char*);
extern void fn_80163DA4(Parser*);
extern void luaK_adjuststack(State*, int);
extern int luaK_jump(State*);
extern void luaK_concat(State*, void*, int);
extern const char lbl_8024F9D0[];

void breakstat(Parser* parser)
{
    State* state = parser->state;
    int position = state->position;
    Node* node = state->node;

    if (node == 0) {
        luaK_error(parser, lbl_8024F9D0);
    }
    fn_80163DA4(parser);
    luaK_adjuststack(state, position - node->position);
    luaK_concat(state, &node->value, luaK_jump(state));
    luaK_adjuststack(state, node->position - position);
}
