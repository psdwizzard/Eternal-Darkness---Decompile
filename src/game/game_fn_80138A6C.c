typedef unsigned int u32;

extern u32 lbl_8064CFFC;
extern u32 lbl_8064D000;
extern unsigned char* lbl_8064D004;
extern u32 lbl_8064CFC0;
extern volatile u32 lbl_8064D00C;
extern volatile u32 lbl_8064D010;
extern char lbl_805AE000[];
extern char lbl_805ADFE0[];

extern void fn_8020D250(void*, int, int);
extern int fn_8020D318(void*, int, int);

void* fn_80138A6C(u32 size, int mode)
{
    u32 aligned;
    unsigned char* result;

    if (mode == 1) {
        u32 old;
        aligned = (size + 31) & ~31;
        old = lbl_8064D000;
        result = lbl_8064D004 + old;
        lbl_8064D000 += aligned;
        if (lbl_8064D000 > lbl_8064CFFC) {
            lbl_8064D000 -= aligned;
            result = 0;
        }
    } else {
        int retry;
        aligned = (size + 31) & ~31;
        retry = 1;
        do {
            result = (unsigned char*)(lbl_8064CFC0 + lbl_8064D010);
            lbl_8064D010 += aligned;
            if (lbl_8064D010 > 0x3D3100 - lbl_8064D00C) {
                if (lbl_8064D00C == 0 || !retry) {
                    result = 0;
                } else {
                    lbl_8064D010 -= aligned;
                    retry = 0;
                    fn_8020D250(lbl_805AE000, 0, 1);
                    fn_8020D318(lbl_805ADFE0, 0, 1);
                }
            } else {
                retry = 1;
            }
        } while (!retry);
    }
    return result;
}
