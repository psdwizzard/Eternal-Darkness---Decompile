typedef unsigned char u8;
typedef unsigned long u32;

typedef struct Data801F33E8 {
    u8 pad000[0x758];
    u8 a[0x10];
    u8 b[0x10];
    u8 c[0x10];
    u8 d[0x10];
} Data801F33E8;

extern Data801F33E8 lbl_8063BEA0;
extern u32 lbl_8064C384, lbl_8064C380;
extern u32 lbl_8064D764, lbl_8064D770;
extern void* memcpy(void*, const void*, u32);

#pragma opt_propagation off
void fn_801F33E8(void)
{
    Data801F33E8* info = &lbl_8063BEA0;
    lbl_8064C384 = lbl_8064C380;
    memcpy(info->b, info->a, 0x10);
    memcpy(info->d, info->c, 0x10);
    lbl_8064D764 = lbl_8064D770;
}
#pragma opt_propagation reset
