extern void *memset(void *, int, unsigned long);
extern int lbl_80642C10[];

int *_make_words(int *lengths, int count) {
    int next_code[33];
    int *table = lbl_80642C10;
    int i;

    memset(next_code, 0, sizeof(next_code));

    for (i = 0; i < count; i++) {
        int length = lengths[i];
        if (length > 0) {
            int code;
            int j = length;

            table[i] = code = next_code[length];
            for (; j > 0; j--) {
                int value = next_code[j];
                if (value & 1) {
                    if (j == 1) {
                        next_code[1]++;
                    } else {
                        next_code[j] = next_code[j - 1] * 2;
                    }
                    break;
                }
                next_code[j] = value + 1;
            }

            for (j = length + 1; j < 33; j++) {
                int value = next_code[j];
                if (code != (value >> 1)) {
                    break;
                }
                code = value;
                next_code[j] = next_code[j - 1] * 2;
            }
        }
    }

    for (i = 0; i < count; i++) {
        int length = lengths[i];
        int reversed = 0;
        int bit = 0;
        if (length > 0) {
            for (; bit < length; bit++) {
                reversed = (reversed << 1) | ((table[i] >> bit) & 1);
            }
        }
        table[i] = reversed;
    }
    return table;
}
