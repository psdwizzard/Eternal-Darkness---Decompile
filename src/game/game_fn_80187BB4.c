typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void fn_80187BB4(u8* self, u8* desc)
{
    self[0x8D] = desc[1];
    *(u32*)(self + 0x90) = *(u32*)(desc + 0x14);
    *(u32*)(self + 0x94) = *(u32*)(desc + 0x18);
    *(u32*)(self + 0x98) = *(u32*)(desc + 0x1C);
    *(u32*)(self + 0x9C) = *(u32*)(desc + 0x20);
    *(u32*)(self + 0xA4) = 0;
    *(u32*)(self + 0xA8) = 1;
    *(u32*)(self + 0xA0) = 0;
    *(float*)(self + 0xD0) = *(s16*)(self + 0x10);
    *(float*)(self + 0xD4) = *(s16*)(self + 0x12);
    *(float*)(self + 0xD8) = *(s16*)(self + 0x14);
    *(u16*)(self + 0xDC) = 0;
    *(u16*)(self + 0xDE) = 0;
    *(u32*)(self + 0xE2) = *(u32*)(desc + 0x30);

    if (*(int*)(desc + 0x20) != 0) {
        *(float*)(self + 0xAC) =
            (desc[0x34] - desc[0x30]) / (float)*(u16*)(desc + 0x2A);
        *(float*)(self + 0xB0) =
            (desc[0x35] - desc[0x31]) / (float)*(u16*)(desc + 0x2A);
        *(float*)(self + 0xB4) =
            (desc[0x36] - desc[0x32]) / (float)*(u16*)(desc + 0x2A);
        *(float*)(self + 0xB8) = desc[0x30];
        *(float*)(self + 0xBC) = desc[0x31];
        *(float*)(self + 0xC0) = desc[0x32];
        *(u16*)(self + 0xE0) = 0;
        *(float*)(self + 0xC4) =
            (desc[1] - (desc[1] >> 1)) / (float)*(u16*)(desc + 0x2A);
    }

    self[0x8C] = desc[0x26];
    *(float*)(self + 0xCC) = *(float*)(desc + 0x2C);
    *(float*)(self + 0xC8) = desc[1] >> 1;
    self[0x8E] = desc[0x27];
}
