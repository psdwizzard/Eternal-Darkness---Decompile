typedef unsigned char u8;
typedef signed char s8;

#define SUB_CLAMP0(a, b) ((a) - (b) > 0 ? (a) - (b) : 0)

extern void fn_8018E8B8(u8*, u8, int);

u8 fn_8018E504(u8* state, u8* object)
{
    u8* channel;
    u8 bit;
    int i;

    if (state[7] != 0) {
        state[7]--;
        if (state[7] == 0) {
            fn_8018E8B8(object, state[4], 0);
            fn_8018E8B8(object, state[4], 1);
            state[0] = 1;
        }
    }

    channel = object + 8;
    bit = 1;
    switch (state[0]) {
    case 1:
        for (i = 0; i < 4; i++, channel += 4, bit <<= 1) {
            if (channel[3] == state[1]) {
                object[7] &= ~bit;
                if (object[7] == 0) {
                    if (state[7] != 0) {
                        state[0] = 7;
                    } else {
                        state[0] = 0;
                    }
                }
            }
            if (object[7] & bit) {
                channel[3] += state[5];
            }
        }
        break;
    case 4:
        if (channel[3] == state[1]) {
            if ((s8)state[5] > 0) {
                state[1] = state[3];
            } else {
                state[1] = state[2];
            }
            state[5] = -state[5];
        }
        for (i = 0; i < 4; i++, channel += 4, bit <<= 1) {
            if (object[7] & bit) {
                channel[3] += state[5];
            }
        }
        break;
    case 2:
        if (channel[3] == state[1]) {
            if (state[3] == state[2]) {
                state[0] = 0;
            } else {
                if ((s8)state[5] > 0) {
                    state[2] = SUB_CLAMP0(state[2], __abs(*(s8*)(state + 5)));
                    state[3] = SUB_CLAMP0(state[3], __abs(*(s8*)(state + 5)));
                    state[1] = state[3];
                } else {
                    state[1] = state[2];
                }
                state[5] = -state[5];
            }
        }
        if (state[0] != 0) {
            for (i = 0; i < 4; i++, channel += 4, bit <<= 1) {
                if (object[7] & bit) {
                    channel[3] += state[5];
                }
            }
        }
        break;
    }
    return state[0];
}
