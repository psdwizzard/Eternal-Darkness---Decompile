typedef unsigned char u8;
typedef unsigned long u32;

typedef struct Data801F338C {
    u8 pad000[0x758];
    u8 a[0x10];
    u8 b[0x10];
    u8 c[0x10];
    u8 d[0x10];
} Data801F338C;

extern Data801F338C lbl_8063BEA0;
extern u32 lbl_8064C384, lbl_8064C380;
extern u32 lbl_8064D764, lbl_8064D770;
extern void* memcpy(void*, const void*, u32);

#pragma opt_propagation off
void fn_801F338C(void)
{
    lbl_8064C380 = lbl_8064C384;
    memcpy(lbl_8063BEA0.a, lbl_8063BEA0.b, 0x10);
    memcpy(lbl_8063BEA0.c, lbl_8063BEA0.d, 0x10);
    lbl_8064D770 = lbl_8064D764;
}
#pragma opt_propagation reset
