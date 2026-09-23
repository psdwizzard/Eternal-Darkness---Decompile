typedef signed short s16;
typedef unsigned char u8;
typedef unsigned int u32;

void fn_80186C88(s16* output, int count, int step, int base, int range);
void fn_80193D64(s16* output, int count, int step, int base, int range);

void fn_801950D4(const s16* base, const s16* step, u8* state)
{
    s16* outputs[3];
    u32 flags;
    u8 width;
    int range;

    width = state[0xB] - 4;
    outputs[0] = (s16*)(state + 0x28);
    outputs[1] = (s16*)(state + 0x42);
    outputs[2] = (s16*)(state + 0x5C);
    flags = *(u32*)(state + 0x7C);
    range = state[3];

    if (flags & 0x100) {
        int rest;
        int stride;
        int fullWidth = width;

        width = (u8)width >> 1;
        fn_80186C88(outputs[0], fullWidth, step[0], base[0], range);
        fn_80186C88(outputs[1], fullWidth, step[1], base[1], range);
        stride = step[2] * 2;
        fn_80193D64(outputs[2], width, stride, base[2], range);
        rest = fullWidth - width;
        fn_80193D64(outputs[2] + width, rest, step[2] / rest,
                    base[2] + width * stride, range);
    } else if (flags & 0x400) {
        int fullWidth = width;
        int rest;
        int stride;

        width = (u8)width >> 1;
        stride = step[0] * 2;
        fn_80193D64(outputs[0], width, stride, base[0], range);
        rest = fullWidth - width;
        fn_80193D64(outputs[0] + width, rest, step[0] / rest,
                    base[0] + width * stride, range);
        stride = step[1] * 2;
        fn_80193D64(outputs[1], width, stride, base[1], range);
        fn_80193D64(outputs[1] + width, rest, step[1] / rest,
                    base[1] + width * stride, range);
        stride = step[2] * 2;
        fn_80193D64(outputs[2], width, stride, base[2], range);
        fn_80193D64(outputs[2] + width, rest, step[2] / rest,
                    base[2] + width * stride, range);
    } else {
        int i;
        for (i = 0; i < 3; i++) {
            fn_80186C88(outputs[i], width, step[i], base[i], range);
        }
    }
}
