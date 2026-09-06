typedef unsigned char u8;
typedef unsigned int u32;

extern void* lbl_8064D544;

void fn_801DA220(int owner, u8 value)
{
    char* node = lbl_8064D544;
    while (node != 0) {
        if (*(int*)(node + 0xC) == owner &&
            (*(int*)(node + 4) & 0x1FF0) == 0x1010 &&
            *(u8*)(node + 0xFF1) == 2) {
            *(u8*)(node + 0xC5) = value;
            if (value != 0)
                return;
            *(u8*)(node + 0xC4) |= 0x10;
            return;
        }
        node = *(char**)(node + 0x14);
    }
}
