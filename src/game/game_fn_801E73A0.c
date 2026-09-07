typedef unsigned int u32;

u32 fn_801E73A0(u32 value, u32 input, u32 polynomial)
{
    int i;
    u32 data = input << 8;

    for (i = 0; i < 8; i++) {
        if ((value ^ data) & 0x8000) {
            value = (value << 1) ^ polynomial;
        } else {
            value <<= 1;
        }
        data <<= 1;
    }
    return value;
}
