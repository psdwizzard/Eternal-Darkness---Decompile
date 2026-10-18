typedef struct InputFunction {
    unsigned char pad00[0x20];
    unsigned short line_defined;
    unsigned short source_line;
    unsigned short num_params;
    unsigned char pad26[0x16];
    int max_stack;
    void* source;
} InputFunction;

extern void* luaF_newproto(void*);
extern void* LoadString(void*, void*, int);
extern int LoadInt(void*, void*, int);
extern int ezgetc(void*, void*);
extern void LoadLocals(void*, void*, void*, int);
extern void LoadLines(void*, void*, void*, int);
extern void LoadConstants(void*, void*, void*, int);
extern void LoadCode(void*, void*, void*, int);

InputFunction* LoadFunction(void* object, void* input, int reverse)
{
    InputFunction* function = luaF_newproto(object);

    function->source = LoadString(object, input, reverse);
    function->max_stack = LoadInt(object, input, reverse);
    function->line_defined = LoadInt(object, input, reverse);
    function->source_line = ezgetc(object, input);
    function->num_params = LoadInt(object, input, reverse);
    LoadLocals(object, function, input, reverse);
    LoadLines(object, function, input, reverse);
    LoadConstants(object, function, input, reverse);
    LoadCode(object, function, input, reverse);
    return function;
}
