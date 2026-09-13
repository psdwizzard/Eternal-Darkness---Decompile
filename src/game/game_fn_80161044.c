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

extern int fn_800F6460(JumpContext*);
extern void fn_801605F4(Object*);

int fn_80161044(Object* object, void (*callback)(Object*, void*), void* argument)
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
    if (fn_800F6460(&context) == 0) {
        callback(object, argument);
    } else {
        object->limit = saved_limit;
        object->start = saved_start;
        object->current = saved_current;
        fn_801605F4(object);
    }
    object->context = *saved_context;
    return *result;
}
