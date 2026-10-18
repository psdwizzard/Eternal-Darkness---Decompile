typedef unsigned int u32;

extern u32 PPCMfhid2(void);
extern void DCInvalidateRange(void*, u32);
extern void LCEnable(void);
extern void* volatile lbl_8064CEFC;
extern volatile u32 lbl_8064CF10;

static inline void SetHID2(void)
{
    asm {
        lis r3, 0x407
        addi r3, r3, 0x407
        mtspr 918, r3
    }
}

void fn_80125284(void)
{
    u32 hid2 = PPCMfhid2();

    if ((hid2 & 0x10000000) == 0) {
        DCInvalidateRange((void*)0xE0000000, 0x4000);
        LCEnable();
    }

    lbl_8064CEFC = (void*)0xE0000000;
    lbl_8064CF10 = 4;
    SetHID2();
}
