typedef struct Object {
    char padding00[108];
    int active;
} Object;

typedef struct Nested {
    char padding00[4];
    int state;
} Nested;

typedef struct Source {
    char padding00[8];
    Nested* nested;
} Source;

typedef struct Context {
    void* handler;
    char padding04[88];
    Source* source;
} Context;

typedef void (*Callback)(Object*, void*);

extern void dohook(Object*, Context*, Callback);

void luaD_callHook(Object* object, Source* source, Callback callback, void* handler)
{
    Context context;

    if (object->active != 0) {
        context.source = source;
        context.handler = handler;
        source->nested->state = 0;
        dohook(object, &context, callback);
    }
}
