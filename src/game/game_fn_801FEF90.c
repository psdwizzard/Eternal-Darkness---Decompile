typedef unsigned int u32;

extern u32 lbl_8064D7D8;
extern u32 lbl_8064D7E8[2];

void fn_801FEF90(signed char* mask, int count, u32* source, u32* output,
                 u32* alternate)
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
    lbl_8064D7E8[lbl_8064D7D8] = count;
}
