typedef unsigned int u32;

#define STEP() \
    if (index > 15) { \
        if (index == 31) { \
            result |= sign; \
        } else { \
            result |= (value & (mask << index)) >> right; \
            right += 2; \
        } \
    } else { \
        result |= (value & (mask << index)) << ((31 - index) - left); \
        left += 1; \
    } \
    index += 1

u32 fn_8021D640(u32 value) {
    u32 sign = value >> 31;
    u32 left = 0;
    u32 right = 1;
    u32 result = 0;
    u32 index = 0;
    u32 mask = 1;
    int i;

    for (i = 8; i > 0; i--) {
        STEP();
        STEP();
        STEP();
        STEP();
    }
    return result;
}
