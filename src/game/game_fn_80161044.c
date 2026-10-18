typedef struct JumpContext {
    char registers[0x190];
    struct JumpContext* volatile saved;
    volatile int result;
} JumpContext;

typedef struct Object {
    void* current;
    void* allocation;
    void* end;
    int count;
    void* start;
    JumpContext* context;
    char _pad18[0x54];
    void* limit;
} Object;

extern int __setjmp(JumpContext*);
extern void restore_stack_limit(Object*);

int luaD_runprotected(Object* object, void (*callback)(Object*, void*), void* argument)
{
    JumpContext context;
    JumpContext* volatile* saved_context;
    volatile int* result;
    void* saved_start = object->start;
    void* saved_current = object->current;
    void* saved_limit = object->limit;

    result = &context.result;
    saved_context = &context.saved;
    *result = 0;
    *saved_context = object->context;
    object->context = &context;
    if (__setjmp(&context) == 0) {
        callback(object, argument);
    } else {
        object->limit = saved_limit;
        object->start = saved_start;
        object->current = saved_current;
        restore_stack_limit(object);
    }
    object->context = *saved_context;
    return *result;
}
