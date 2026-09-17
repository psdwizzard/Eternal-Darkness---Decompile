typedef unsigned char u8;

typedef struct Entry {
    u8 value;
    u8 pad[7];
} Entry;

/*
 * Retail probes byte offsets 0x0, 0x8, 0x10, and 0x18 from lbl_80607CB0.
 * The symbol owns 0x20 bytes, establishing four eight-byte entries here.
 */
extern Entry lbl_80607CB0[4];

int fn_801A9B38(void)
{
    int result = 100;
    volatile Entry* entry = lbl_80607CB0;
    int value;
    int i;

    #pragma unroll 4
    for (i = 0; i < 4; i++) {
        value = entry->value;
        if (value < result) {
            result = value;
        }
        entry++;
    }
    return result;
}
