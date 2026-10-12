int fn_800FD228(const char* left, const char* right)
{
    const unsigned char* a = (const unsigned char*)left;
    const unsigned char* b = (const unsigned char*)right;
    unsigned int ch;
    unsigned long alignment;
    unsigned long count;
    unsigned long word_a;
    unsigned long word_b;
    int difference;

    ch = *a;
    if ((difference = ch - *b) != 0) {
        return difference;
    }
    if (((unsigned long)b & 3) == (alignment = (unsigned long)a & 3)) {
        if (alignment != 0) {
            if (ch == 0) {
                return 0;
            }
            count = 3 - alignment;
            for (; count != 0; --count) {
                ch = *++a;
                if ((difference = ch - *++b) != 0) {
                    return difference;
                }
                if (ch == 0) {
                    return 0;
                }
            }
            ++a;
            ++b;
        }
        word_a = *(const unsigned long*)a;
        word_b = *(const unsigned long*)b;
        if (((word_a - 0x01010101) & 0x80808080) != 0) {
            goto byte_compare;
        }
        while (word_a == word_b) {
            a += 4;
            b += 4;
            word_a = *(const unsigned long*)a;
            word_b = *(const unsigned long*)b;
            if (((word_a - 0x01010101) & 0x80808080) != 0) {
                goto byte_compare;
            }
        }
        return word_a > word_b ? 1 : -1;
byte_compare:
        ch = *a;
        if ((difference = ch - *b) != 0) {
            return difference;
        }
    }
    if (ch == 0) {
        return 0;
    }
    do {
        ch = *++a;
        if ((difference = ch - *++b) != 0) {
            return difference;
        }
    } while (ch != 0);
    return 0;
}
