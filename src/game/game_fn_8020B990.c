typedef unsigned int u32;

/* Start a locked-cache DMA load, encoding the block count in both registers. */
void LCLoadBlocks(void *destination, void *source, u32 blocks)
{
    register u32 control;

    control = (blocks >> 2) & 0x1F;
    source = (void *)((u32)source & 0x0FFFFFFF);
    control |= (u32)source;
    /* ASM: mtspr writes DMA_U, a hardware register inaccessible to C. */
    asm { mtspr 922, control }

    control = ((blocks & 3) << 2) | (u32)destination;
    control |= 0x12;
    /* ASM: mtspr writes DMA_L to start the transfer; C cannot access it. */
    asm { mtspr 923, control }
}
