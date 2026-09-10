typedef unsigned short u16;
typedef unsigned int u32;

#pragma pack(1)
typedef struct Record6 {
    u32 word;
    u16 half;
} Record6;
#pragma pack()

extern u32 lbl_8064D7D8;
extern u32 lbl_8064D800[2];

void fn_801FEE10(signed char* mask, int count, Record6* source, Record6* output,
                 Record6* alternate)
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
    lbl_8064D800[lbl_8064D7D8] = count;
}
