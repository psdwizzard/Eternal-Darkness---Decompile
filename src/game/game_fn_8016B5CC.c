extern int lbl_805FAAD8[1537];
extern void* lbl_8064C3C8;
extern int lbl_8064D1B8;
extern char* lbl_8064D1C8;
extern char lbl_8024FEDC[];

extern void fn_8020AFE4(void*);
extern void* memset(void*, int, unsigned int);
extern void* memcpy(void*, const void*, unsigned int);

void* fn_8016B5CC(void* context, void* allocation, int size,
                  const char* file, int line)
{
    int words;
    int offset;
    int index;
    void* replacement;
    int value;

    fn_8020AFE4(lbl_8064C3C8);

    if (size < 0) {
        lbl_8064D1B8 = 0;
        memset(lbl_805FAAD8, 0, sizeof(lbl_805FAAD8));
        lbl_805FAAD8[0] = 0x25BB8;
    } else if (allocation == 0) {
        words = (size + 3) / 4;
        offset = 0;
        if (words == 0) {
            return 0;
        }

        for (index = 0; index < 1536; index++) {
            value = lbl_805FAAD8[index];
            if (words < value) {
                if (lbl_805FAAD8[index + 1] == 0) {
                    lbl_805FAAD8[index + 1] = lbl_805FAAD8[index] - words;
                    lbl_805FAAD8[index] = -words;
                } else {
                    lbl_805FAAD8[index] = -lbl_805FAAD8[index];
                }
                lbl_8064D1B8 -= lbl_805FAAD8[index];
                return lbl_8064D1C8 + offset * 4;
            }
            offset += value < 0 ? -value : value;
        }
    } else {
        words = (size + 3) / 4;
        if (words == 0) {
            int covered = 0;
            int target = ((char*)allocation - lbl_8064D1C8) / 4;

            for (index = 0; index < 1536; index++) {
                value = lbl_805FAAD8[index];
                covered += value < 0 ? -value : value;
                if (covered > target) {
                    break;
                }
            }

            lbl_8064D1B8 += lbl_805FAAD8[index];
            lbl_805FAAD8[index] = -lbl_805FAAD8[index];
            if (index < 1535 && lbl_805FAAD8[index + 1] > 0) {
                lbl_805FAAD8[index] += lbl_805FAAD8[index + 1];
                lbl_805FAAD8[index + 1] = 0;
            }
            for (; index > 0; index--) {
                if (lbl_805FAAD8[index - 1] < 0) {
                    break;
                }
                lbl_805FAAD8[index - 1] += lbl_805FAAD8[index];
                lbl_805FAAD8[index] = 0;
            }
            allocation = 0;
        } else {
            words *= 4;
            replacement = fn_8016B5CC(context, 0, words, lbl_8024FEDC, 0x36F);
            memcpy(replacement, allocation, words);
            fn_8016B5CC(context, allocation, 0, lbl_8024FEDC, 0x371);
            allocation = replacement;
        }
    }

done:
    fn_8020AFE4(lbl_8064C3C8);
    return allocation;
}
