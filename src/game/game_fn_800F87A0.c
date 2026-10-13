typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;

typedef struct Decimal {
    u8 sign;
    u8 pad0;
    s16 exponent;
    u8 length;
    u8 digits[0x24];
} Decimal;

void fn_800F87A0(Decimal *out, const Decimal *left, const Decimal *right)
{
    u8 work[0x48];
    u8 *end;
    u8 *limit;
    u32 carry = 0;
    int column;
    int i;

    out->sign = 0;
    out->length = 0;
    column = left->length + right->length - 1;
    limit = &work[column + 1];
    end = limit;
    while (column > 0) {
        int rightStart = right->length - 1;
        int leftStart = (column - rightStart) - 1;
        int count;
        int j;

        if (leftStart < 0) {
            leftStart = 0;
            rightStart = column - 1;
        }
        count = rightStart + 1;
        if (count > left->length - leftStart)
            count = left->length - leftStart;
        for (j = 0; j < count; j++)
            carry += left->digits[leftStart + j] * right->digits[rightStart - j];
        column--;
        *--end = (u8)(carry % 10);
        carry /= 10;
    }

    out->exponent = left->exponent + right->exponent;
    if (carry != 0) {
        *--end = (u8)carry;
        out->exponent++;
    }
    for (i = 0; i < 0x24 && end < limit; i++)
        out->digits[i] = *end++;
    out->length = (u8)i;
    if (end < limit && *end >= 5) {
        int round = *end++;
        if (round == 5) {
            while (end < limit && *end == 0)
                end++;
            if ((end[-1] & 1) == 0)
                return;
        }
        i = out->length - 1;
        for (;;) {
            if (out->digits[i] < 9) {
                out->digits[i]++;
                return;
            }
            if (i == 0) {
                out->digits[i] = 1;
                out->exponent++;
                return;
            }
            out->digits[i--] = 0;
        }
    }
}
