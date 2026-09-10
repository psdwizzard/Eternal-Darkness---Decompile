typedef unsigned int u32;

typedef struct Context {
    unsigned char pad[8];
    u32 size;
    u32 count;
} Context;

extern void fn_801FF750(void** owner, u32 size, void* replacement);

void fn_801FF7D4(Context* context, u32* cursor)
{
    u32 replacement = *cursor;
    u32 count;
    u32 size;

    fn_801FF750((void**)context, context->size, (void*)replacement);
    count = context->count;
    size = context->size;
    context->count = count + 1;
    replacement += size;
    *cursor = replacement;
}
