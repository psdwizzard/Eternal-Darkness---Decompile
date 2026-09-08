extern void fn_801EF7C0(void);

void fn_801EF788(void)
{
    fn_801EF7C0();
    asm {
        lis r3, 0x0E07
        addi r3, r3, 0x0E07
        mtspr 919, r3
        lis r3, 0x0407
        addi r3, r3, 0x0407
        mtspr 914, r3
    }
}
