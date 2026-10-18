typedef struct Object {
    char padding00[108];
    int active;
} Object;

typedef struct Context {
    void* handler;
    void* value;
    char padding08[84];
    void* source;
} Context;

typedef void (*Callback)(Object*, void*);

extern char lbl_8064BA60;
extern void dohook(Object*, Context*, Callback);

void luaD_lineHook(Object* object, void* source, void* value, Callback callback)
{
    Context context;

    if (object->active != 0) {
        context.source = source;
        context.value = value;
        context.handler = &lbl_8064BA60;
        dohook(object, &context, callback);
    }
}
