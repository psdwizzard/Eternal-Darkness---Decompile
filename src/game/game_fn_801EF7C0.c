void fn_801EF7C0(void)
{
    asm {
        li r3, 4
        oris r3, r3, 4
        mtspr 914, r3
        li r3, 5
        oris r3, r3, 5
        mtspr 915, r3
        li r3, 6
        oris r3, r3, 6
        mtspr 916, r3
        li r3, 7
        oris r3, r3, 7
        mtspr 917, r3
    }
}
