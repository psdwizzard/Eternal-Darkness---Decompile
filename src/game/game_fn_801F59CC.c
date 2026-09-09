typedef unsigned short u16;
typedef unsigned long size_t;

extern void* lbl_8064D790;
extern u16 lbl_8064D788;
extern u16 lbl_8064D78A;

extern void* memset(void*, int, size_t);

void fn_801F59CC(void)
{
    memset(lbl_8064D790, 0, lbl_8064D788 * 12);
    lbl_8064D78A = 0;
}
