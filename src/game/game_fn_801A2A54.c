typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern const float lbl_80650D1C;
extern const double lbl_80650D20;

void fn_801A2A54(u8* object, int value)
{
    *(u16*)(object + 0xA) = 1;
    *(u32*)(object + 0x44) = 1;
    *(u16*)(object + 0xC) = 31;
    *(float*)(object + 0x90) = lbl_80650D1C;
    *(float*)(object + 0x98) = *(float*)(object + 0x94) / *(u16*)(object + 0xC);
    if (value == 0) {
        *(u16*)(object + 0x22) = 8;
    }
}
