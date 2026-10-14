/* Dolphin SDK OSReset.c: report a software reboot or the hardware reset code. */
typedef unsigned char u8;
typedef unsigned int u32;

u32 OSGetResetCode(void) {
    register u32 code;

    if (*(u8 *)0x800030E2 != 0) {
        code = 0x80000000;
    } else {
        register volatile u32 *regs;
        register u32 raw;

        /* ASM: lis, addi, lwz, clrrwi, srwi retain the hardware register
         * base and separate mask/shift. C folds the base into the load
         * displacement and removes the mask before the unsigned shift. */
        asm {
            lis regs, 0xCC00
            addi regs, regs, 0x3000
            lwz raw, 0x24(regs)
            clrrwi raw, raw, 3
            srwi code, raw, 3
        }
    }
    return code;
}
