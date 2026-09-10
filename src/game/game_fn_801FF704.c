typedef struct Context {
    void* object;
    unsigned char pad[0xC];
    struct Context* head;
} Context;

extern void fn_801FF6F4(Context* context);

void fn_801FF704(Context* context)
{
    Context* node = context->head;

    context->head = 0;
    while (node != 0) {
        Context* next = node->head;
        fn_801FF6F4(node);
        node = next;
    }
}
