typedef struct Value {
    int type;
    int unused;
    double data;
} Value;

typedef struct State State;

extern char lbl_8024FCB8[];
extern int call_binTM(State*, Value*, int);
extern void luaG_binerror(State*, Value*, int, char*);

void call_arith(State* state, Value* value, int index)
{
    if (!call_binTM(state, value, index)) {
        luaG_binerror(state, value - 2, 2, lbl_8024FCB8);
    }
}
