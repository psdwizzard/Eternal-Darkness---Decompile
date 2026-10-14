/* Invalidate the entire instruction cache through HID0's ICFI bit. */
void ICFlashInvalidate(void)
{
    register unsigned int hid0;

    /* ASM: mfspr reads HID0, a hardware register inaccessible through C. */
    asm { mfspr hid0, 1008 }
    hid0 |= 0x0800;
    /* ASM: mtspr writes HID0, a hardware register inaccessible through C. */
    asm { mtspr 1008, hid0 }
}
