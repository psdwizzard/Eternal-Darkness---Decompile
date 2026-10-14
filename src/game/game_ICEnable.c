/* Enable the instruction cache in the hardware implementation register. */
void ICEnable(void)
{
    register unsigned int hid0;

    __isync();
    /* ASM: mfspr reads HID0, a hardware register inaccessible through C. */
    asm { mfspr hid0, 1008 }
    hid0 |= 0x8000;
    /* ASM: mtspr writes HID0, a hardware register inaccessible through C. */
    asm { mtspr 1008, hid0 }
}
