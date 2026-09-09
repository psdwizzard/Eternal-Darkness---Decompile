typedef unsigned char u8;
typedef unsigned long u32;

extern u8 lbl_8063C608[0x10];
extern u8 lbl_8063C628[0x10];
extern void* memset(void*, int, u32);
extern void fn_801F338C(void);

void fn_801F3444(void)
{
    memset(lbl_8063C608, 0, 0x10);
    memset(lbl_8063C628, 0, 0x10);
    fn_801F338C();
}
