typedef unsigned int u32;

typedef struct Record8 {
    u32 first;
    u32 second;
} Record8;

extern u32 lbl_8064D7D8;
extern u32 lbl_8064D7F8[2];

void fn_801FEE98(signed char* mask, int count, Record8* source,
                 Record8* output, Record8* alternate)
{
    int i;

    for (i = 0; i < count; i++) {
        if (mask[i >> 3] & (1 << (i & 7))) {
            *output++ = *alternate++;
        } else {
            *output++ = *source;
        }
        if (source != 0) {
            source++;
        }
    }
    lbl_8064D7F8[lbl_8064D7D8] = count;
}
