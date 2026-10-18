typedef struct Context {
    void* current;
    char pad04[4];
    void* end;
    char pad0C[0x40];
    int limit;
} Context;

typedef struct Value {
    int type;
    int pad04;
    void* value;
} Value;

extern char lbl_8024FE6C[];
extern void luaO_verror(void*, const char*, ...);
extern void* luaS_createudata(Context*, void*, int);
extern void luaD_checkstack(Context*, int);

void lua_pushusertag(Context* context, void* value, int index)
{
    if ((unsigned)(index + 1) > 1) {
        if (index < 6 || index > context->limit) {
            luaO_verror(context, lbl_8024FE6C, index);
        }
    }
    ((Value*)context->current)->value = luaS_createudata(context, value, index);
    ((Value*)context->current)->type = 0;
    if (context->current == context->end) {
        luaD_checkstack(context, 1);
    }
    context->current = (char*)context->current + 16;
}
