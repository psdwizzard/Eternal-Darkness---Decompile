typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

extern int lbl_8064C64C;
extern int lbl_8064D6E4;
extern u8* lbl_8064D718;
extern u8* lbl_8064D71C[2];
extern int lbl_8064D734;
extern int lbl_8064D738;

extern u8* fn_801EB080(void);
extern void DCFlushRange(void*, u32);
extern void fn_801A99B4(void);
extern void VISetNextFrameBuffer(void*);
extern void fn_801EFE84(int);
extern void VIFlush(void);
extern void VIWaitForRetrace(void);

void fn_80025AA4(void)
{
    int frame;
    int size = 0x4B000;

    for (frame = 0; frame < 60; frame++) {
        int i;
        u8* destination = fn_801EB080();
        u32 root = (u32)lbl_8064D718;
        u8* output = (u8*)root;
        u8* source = (u8*)root;
        u8* input = (u8*)root;

        for (i = 0; i < size; i++) {
            int value = *input - 5;
            *output = MAX(0, value);
            lbl_8064C64C++;
            output[1] = 0x80;
            input += 2;
            output += 2;
        }

        DCFlushRange(source, 0x96000);
        fn_801A99B4();
        VISetNextFrameBuffer(lbl_8064D718);
        fn_801EFE84(0);
        VIFlush();
        VIWaitForRetrace();

        lbl_8064D734 = lbl_8064D6E4;
        lbl_8064D6E4++;
        lbl_8064D6E4 &= 1;
        lbl_8064D738 ^= 1;
        {
            for (i = 0; i < size; i++) {
                destination[0] = source[0];
                destination[1] = source[1];
                source += 2;
                destination += 2;
            }
        }

        if (lbl_8064D718 == lbl_8064D71C[1]) {
            lbl_8064D718 = lbl_8064D71C[0];
        } else {
            lbl_8064D718 = lbl_8064D71C[1];
        }
    }
}
