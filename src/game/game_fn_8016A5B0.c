typedef struct Context {
    char* top;
    char pad04[12];
    char* stack;
} Context;

extern void fn_80160628(Context*, char*, int);

void fn_8016A5B0(Context* context, int count)
{
    if (count >= 0) {
        fn_80160628(context, context->stack, count);
    } else {
        context->top = context->top + 16 + (count << 4);
    }
}
