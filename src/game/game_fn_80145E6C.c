extern void* memset(void*, int, unsigned int);
extern void fn_80145E60(void*, void*, void*);

typedef struct StreamContext {
    unsigned char bytes[0x2AD8];
} StreamContext;

#pragma use_lmw_stmw on
void fn_80145E6C(StreamContext* context, void* write_callback, void* read_callback,
                 int callback_arg, int limit)
{
    memset(context, 0, sizeof(*context));
    *(int*)&context->bytes[0x2010] = limit;
    *(int*)&context->bytes[0x200C] = limit;
    *(int*)&context->bytes[0x2000] = 0;
    *(int*)&context->bytes[0x2004] = 0;
    *(int*)&context->bytes[0x2008] = 0;
    fn_80145E60(context, write_callback, read_callback);
    *(int*)&context->bytes[0x2ACC] = callback_arg;
}
#pragma use_lmw_stmw reset
