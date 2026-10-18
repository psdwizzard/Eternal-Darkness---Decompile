typedef unsigned char u8;
typedef unsigned int u32;

extern void* lbl_8064D1A0;
extern u8 lbl_805B6FFC[];
extern u32 fn_8015A2E0(void*);
extern void OSSendMessage(void*, u32, int);

void fn_8015DF24(void)
{
    u32 result = fn_8015A2E0(lbl_8064D1A0);
    result |= 0x10000000;
    OSSendMessage(lbl_805B6FFC, result, 1);
}
