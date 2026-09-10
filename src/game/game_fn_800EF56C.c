typedef unsigned char u8;
typedef unsigned int u32;

typedef struct TRKBuffer {
    u32 unk0;
    u32 unk4;
    u32 length;
    u32 position;
    u8 data[1];
} TRKBuffer;

extern void fn_80003130(void *, const void *, u32);

#pragma opt_propagation off
int fn_800EF56C(TRKBuffer *buffer, u8 *out, int count)
{
    int read_err;
    u32 amount;
    int i = 0;
    int err = 0;

    while (err == 0 && i < count) {
        u32 remaining;

        amount = 1;
        read_err = 0;
        remaining = buffer->length - buffer->position;
        if (amount > remaining) {
            read_err = 0x302;
            amount = remaining;
        }
        fn_80003130(out + i, buffer->data + buffer->position, amount);
        buffer->position += amount;
        err = read_err;
        i++;
    }
    return err;
}
#pragma opt_propagation reset
