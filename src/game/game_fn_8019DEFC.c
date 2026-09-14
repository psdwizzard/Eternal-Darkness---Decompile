typedef unsigned char u8;
typedef signed short s16;

void fn_8019DEFC(u8* object)
{
    u8* state;
    int i;
    s16 delta;

    state = object + 0x8C;
    delta = 0;
    i = 0;

    while (i < object[1]) {
        state[i + 0x4F] = 0;
        if (((s16*)state)[i + 6] <= 0) {
            ((s16*)state)[i + 6] = delta;
            delta -= state[0x71];
        } else {
            state[i + 0x4F] = 1;
        }
        i++;
    }
    *(s16*)(state + 0x4C) = delta;
}
