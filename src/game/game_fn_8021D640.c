typedef unsigned int u32;

u32 bitrev(u32 value) {
    u32 sign = value >> 31;
    u32 result;
    u32 i;
    u32 left = 0;
    u32 right = 1;

    result = 0;

    for (i = 0; i < 32; i++) {
        if (i > 15) {
            if (i == 31) {
                result |= sign;
            } else {
                result |= (value & (1 << i)) >> right;
                right += 2;
            }
        } else {
            result |= (value & (1 << i)) << ((31 - i) - left);
            left += 1;
        }
    }
    return result;
}
