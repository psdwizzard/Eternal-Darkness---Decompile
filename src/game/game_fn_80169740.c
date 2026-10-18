typedef struct Value {
    int type;
    int pad04;
    union {
        double number;
        void* pointer;
    } value;
} Value;

typedef struct Context {
    Value* stack;
} Context;

extern void luaD_adjusttop(Context*, Value*, int);
extern void luaV_pack(Context*, Value*);

void adjust_varargs(Context* context, Value* source, int count)
{
    if (context->stack - source - count < 0) {
        luaD_adjusttop(context, source, count);
    }
    luaV_pack(context, source + count);
}
