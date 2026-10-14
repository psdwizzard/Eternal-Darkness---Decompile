/* Enable the data cache after completing outstanding memory operations. */
void DCEnable(void)
{
    register unsigned int hid0;

    __sync();
    /* ASM: mfspr reads HID0, a hardware register inaccessible to C. */
    asm { mfspr hid0, 1008 }
    hid0 |= 0x4000;
    /* ASM: mtspr writes HID0, a hardware register inaccessible to C. */
    asm { mtspr 1008, hid0 }
}
