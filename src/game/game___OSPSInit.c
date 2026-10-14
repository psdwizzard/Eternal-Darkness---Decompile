/* Enable paired-single instructions and initialize their quantization. */

typedef unsigned int u32;

extern u32 PPCMfhid2(void);
extern void PPCMthid2(u32 value);
extern void ICFlashInvalidate(void);
extern void __sync(void);

void __OSPSInit(void) {
    PPCMthid2(PPCMfhid2() | 0xA0000000);
    ICFlashInvalidate();
    __sync();

    /* ASM: li and mtspr initialize GQR0 through r3. C cannot write GQR0,
     * and passing a C zero to inline assembly makes MWCC use r0. */
    asm {
        li r3, 0
        mtspr GQR0, r3
    }
}
