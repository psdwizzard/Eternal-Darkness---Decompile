typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct Buffer801A82FC {
    u8 pad[0x10];
    u16 count;
    u8 pad12[2];
    void* data;
} Buffer801A82FC;

typedef struct Context801A82FC {
    u8 pad[0xA0];
    Buffer801A82FC buffer;
    u8 padB8[0x808A];
    signed char active;
    signed char ready;
} Context801A82FC;

extern Context801A82FC* fn_8015C28C(int);

/* NonMatching: size-exact honest C at 98.690475%. Canonical GC/1.3 uses
 * buffer/data-base/byte-offset in r4/r3/r6; retail uses r6/r4/r3. */
void* fn_801A82FC(u32 value)
{
    Context801A82FC* context = fn_8015C28C(2);
    void* result = 0;

    if (context != 0 && context->active != 0 && context->ready != 0) {
        Buffer801A82FC* buffer = &context->buffer;
        if (buffer != 0) {
            u32 offset = 0;
            int index = 0;

            while (index < buffer->count) {
                if (value == *(u32*)((u8*)buffer->data + offset + 0x2C)) {
                    result = (u8*)buffer->data + index * 0x74;
                    break;
                }
                offset += 0x74;
                index++;
            }
        }
    }

    return result;
}
