typedef struct Context {
    void* object;
    unsigned char pad[0xC];
    void* head;
} Context;

void fn_801FF6F4(Context* context)
{
    context->object = 0;
    context->head = 0;
}
