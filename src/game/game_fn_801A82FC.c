typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct Record801A82FC {
    u8 pad[0x2C];
    u32 key;
    u8 rest[0x44];
} Record801A82FC;

typedef struct Buffer801A82FC {
    u8 pad[0x10];
    u16 count;
    u8 pad12[2];
    Record801A82FC* data;
} Buffer801A82FC;

typedef struct Context801A82FC {
    u8 pad[0xA0];
    Buffer801A82FC buffer;
    u8 padB8[0x808A];
    signed char active;
    signed char ready;
} Context801A82FC;

extern Context801A82FC* fn_8015C28C(int);

/* Typed record indexing lets GC/1.3 generate the retail induction variables. */
void* fn_801A82FC(u32 value)
{
    Context801A82FC* context = fn_8015C28C(2);
    void* result = 0;

    if (context != 0 && context->active != 0 && context->ready != 0) {
        Buffer801A82FC* buffer = &context->buffer;
        if (buffer != 0) {
            int index = 0;

            while (index < buffer->count) {
                if (value == buffer->data[index].key) {
                    result = &buffer->data[index];
                    break;
                }
                index++;
            }
        }
    }

    return result;
}
