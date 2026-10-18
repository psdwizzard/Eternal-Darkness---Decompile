typedef unsigned int u32;
typedef unsigned char u8;

extern u32 lbl_8064D1A0;
extern u8 lbl_805B6FFC[];
extern u32 fn_8017BA24(void);
extern u32 fn_8017B7DC(void);
extern void* fn_8015A1C0(int, u32, u32);
extern u32 fn_8015A2E0(void*);
extern void OSSendMessage(void*, u32, int);

void fn_8015DEC4(void)
{
    u32 second = fn_8017BA24();
    u32 first = fn_8017B7DC();
    void* entry = fn_8015A1C0(1, first, second);
    u32 result;
    lbl_8064D1A0 = (u32)entry;
    result = fn_8015A2E0(entry);
    result |= 0x08000000;
    OSSendMessage(lbl_805B6FFC, result, 1);
}
