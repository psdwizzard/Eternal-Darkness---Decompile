typedef unsigned char u8;
typedef unsigned int u32;

extern int lbl_8064D6FC;

extern void GXGetGPStatus(u8*, u8*, u8*, u8*, u8*);
extern void GXGetFifoStatus(void*, u8*, u8*, u32*, u8*, u8*, u8*);
extern void __GXAbortWaitPECopyDone(void);

void fn_801EFDF4(void)
{
    u8 field_11;
    u8 field_10;
    u8 field_F;
    u8 field_E;
    u8 field_D;
    u8 field_C;
    u8 field_B;
    u8 field_A;
    u8 field_9;
    u8 field_8;
    u32 field_14;
    u8 data[0x80];

    GXGetGPStatus(&field_11, &field_10, &field_F, &field_E, &field_D);
    GXGetFifoStatus(data, &field_C, &field_B, &field_14, &field_A, &field_9,
                &field_8);
    if (field_D != 0 && field_11 != 0) {
        __GXAbortWaitPECopyDone();
    }
    if (lbl_8064D6FC != 0 && field_B != 0) {
        lbl_8064D6FC = 0;
    }
}
