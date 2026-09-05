typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

u32 fn_800FBFB0(void);
void fn_801952E8(void* output, int value);
void* memcpy(void* destination, const void* source, unsigned long count);
void* memset(void* destination, int value, unsigned long count);

void fn_801947F4(u8* output, const u8* input)
{
    int count = (u8)(input[0x17] - 4);

    output[0x8C] = input[0x17] + 1 + (fn_800FBFB0() & 7);
    output[0x8D] = 0;
    output[0x8E] = 0;
    output[0x8F] = input[0x18];
    output[0x98] = input[0x19];
    *(u16*)(output + 0x9C) = 2;
    output[0x90] = input[0x14];
    output[0x91] = input[0x15];
    *(u32*)(output + 0x108) = *(const u32*)(input + 0x38) & 0x3FFFF;

    if ((*(const u32*)(input + 0x38) & 0x20) != 0) {
        output[0x8C] += input[0x17];
    }
    output[0x92] = 0;
    output[0x93] = 0;
    output[0x94] = input[0x16];
    output[0x95] = 0;
    output[0x96] = 0;
    output[0x97] = input[0x17];
    output[0x99] = input[0x1A];
    output[0x9A] = input[0x1B];

    *(u16*)(output + 0xB2) = input[0x17] + ((int)fn_800FBFB0() % count);
    *(u16*)(output + 0xAE) = 0;
    *(u16*)(output + 0xB0) = 0;
    *(u32*)(output + 0x118) = *(const u32*)(input + 0x28);
    *(u32*)(output + 0x11C) = *(const u32*)(input + 0x2C);
    *(u32*)(output + 0x120) = *(const u32*)(input + 0x30);
    memcpy(output + 0xA2, input + 0x22, 6);

    count *= 2;
    memset(output + 0xB4, 0, count);
    memset(output + 0xCE, 0, count);
    memset(output + 0xE8, 0, count);

    if ((*(const u32*)(input + 0x38) & 0x80000) == 0) {
        fn_801952E8(output, 1);
    }
    *(u32*)(output + 0x104) = *(const u32*)(input + 0x34);
    *(u32*)(output + 0x124) = *(const u32*)(input + 0x3C);
    *(u32*)(output + 0x128) = *(const u32*)(input + 0x40);
}
