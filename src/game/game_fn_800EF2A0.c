typedef unsigned char u8;
typedef unsigned int u32;
typedef struct TRKBuffer {
    u32 mutex, in_use, length, position;
    u8 data[0x880];
} TRKBuffer;

extern int fn_800F564C(unsigned char value);
extern int fn_800F5674(void);

int fn_800EF2A0(TRKBuffer *buffer)
{
    u8 checksum;
    u32 i;
    u32 j;
    u8 sum = 0;
    u8 value;
    int result;
    u8 final_value;

    for (i = 0; i < buffer->length; i++) {
        sum = (u8)(sum + buffer->data[i]);
    }
    checksum = (u8)(sum ^ 0xFF);

    result = fn_800F564C(0x7E);
    if (result == 0) {
        for (j = 0; j < buffer->length; j++) {
            value = buffer->data[j];
            if (value == 0x7E || value == 0x7D) {
                result = fn_800F564C(0x7D);
                value ^= 0x20;
                if (result != 0) break;
            }
            result = fn_800F564C((signed char)value);
            if (result != 0) break;
        }
    }
    if (result == 0) {
        final_value = checksum;
        if (final_value == 0x7E || final_value == 0x7D) {
            result = fn_800F564C(0x7D);
            final_value ^= 0x20;
            if (result != 0) goto checksum_done;
        }
        result = fn_800F564C((signed char)final_value);
    }
checksum_done:
    if (result == 0) result = fn_800F564C(0x7E);
    if (result == 0) return fn_800F5674();
    return result;
}
