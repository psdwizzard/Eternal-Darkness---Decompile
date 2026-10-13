extern void *memset(void *, int, unsigned long);
extern int lbl_80642C10[];

int *fn_80235EC4(int *lengths, int count) {
    int next_code[33];
    int *input;
    int *output;
    int i;

    memset(next_code, 0, 0x84);

    input = lengths;
    output = lbl_80642C10;
    for (i = 0; i < count; i++) {
        int length = *input;
        if (length > 0) {
            int code = next_code[length];
            int j = length;

            *output = code;
            while (j > 0) {
                int value = next_code[j];
                if (value & 1) {
                    if (j == 1) {
                        next_code[1]++;
                    } else {
                        next_code[j] = next_code[j - 1] * 2;
                    }
                    break;
                } else {
                    next_code[j] = value + 1;
                    j--;
                }
            }

            j = length + 1;
            while (j < 33 && code == (next_code[j] >> 1)) {
                code = next_code[j];
                next_code[j] = next_code[j - 1] * 2;
                j++;
            }
        }
        input++;
        output++;
    }

    input = lengths;
    output = lbl_80642C10;
    for (i = 0; i < count; i++) {
        int length = *input;
        int bit;
        int reversed = 0;
        if (length > 0) {
            for (bit = 0; bit < length; bit++) {
                reversed = (reversed << 1) | ((*output >> bit) & 1);
            }
        }
        *output = reversed;
        input++;
        output++;
    }
    return lbl_80642C10;
}
