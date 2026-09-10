typedef unsigned int u32;

extern u32 lbl_8064D7D8;
extern u32 lbl_8064D7F0[2];

void fn_801FEF20(signed char* mask, int count, u32* source, u32* output,
                 u32* alternate)
{
    int i;

    for (i = 0; i < count; i++) {
        if (mask[i >> 3] & (1 << (i & 7))) {
            *output++ = *alternate++;
        } else {
            *output++ = *source++;
        }
    }
    lbl_8064D7F0[lbl_8064D7D8] = count;
}
